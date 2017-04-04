#include "core\systems\Input.h"
#include "defines\SystemType.h"
#include "defines\deletemacros.h"

//I really don't like this include since this is here just because I need the keyCodes
#include <SDL\SDL.h>
#include "interfaces\IInput.h"

namespace fractal {
	namespace fcore {
		Input::Input() :
			System(SystemType::INPUT_SYSTEM)
		{
			//empty
		}

		Input::~Input()
		{
			//empty
		}

		bool Input::initialize() {
			//nothing to init for now
			for (IInput* it : m_inputComponents) {
				it->setupInput(this);
			}
			return true;
		}

		void Input::update() {
			//loop through _keymap, and copy it over to _previousKeyMap
			for (auto& it : m_keyMap) {
				//it->first gets the key of the map
				m_previousKeyMap[it.first] = it.second;
			}

			//reset the sdl quit event since there's no keyup for it
			m_keyMap[SDL_QUIT * 2] = false;


			m_oldMousePosition = m_currentMousePosition;
			SDL_Event evnt;
			//Will keep looping until there are no more events to process
			while (SDL_PollEvent(&evnt)) {
				switch (evnt.type) {
				case SDL_QUIT:
					// TODO this is a temporary solution for the closing window event
					// the times two its so it doesn't overlap any other existing event
					pressKey(evnt.type * 2);
					break;
				case SDL_MOUSEMOTION:
					// TODO create a custom event type for mouse motion since there's none
					m_currentMousePosition.x = (float)evnt.motion.x;
					m_currentMousePosition.y = (float)evnt.motion.y;

					//printf("mouse %f,%f\n", m_currentMousePosition.x, m_currentMousePosition.y);
					//_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
					break;
				case SDL_KEYDOWN:
					pressKey(evnt.key.keysym.sym);
					//printf("press %d\n", evnt.key.keysym.sym);
					break;
				case SDL_KEYUP:
					releaseKey(evnt.key.keysym.sym);
					//printf("released %d\n", evnt.key.keysym.sym);
					break;
				case SDL_MOUSEBUTTONDOWN:
					pressKey(evnt.button.button);
					//printf("mb down %d\n", evnt.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					releaseKey(evnt.button.button);
					//printf("mb up %d\n", evnt.button.button);
					break;
				}
			}
			for (MouseBinding binding : m_mouseBindings) {
				switch (binding.inputStateType)
				{
				case InputStateType::MOUSE_DOWN:
					if (isKeyDown(binding.keyID)) {
						binding.execute(getMousePosition());
					}
					break;
				case InputStateType::MOUSE_UP:
					if (isKeyUp(binding.keyID)) {
						binding.execute(getMousePosition());
					}
					break;
				case InputStateType::MOUSE_PRESSED:
					if (wasKeyPressed(binding.keyID)) {
						binding.execute(getMousePosition());
					}
					break;
				case InputStateType::MOUSE_RELEASED:
					if (wasKeyReleased(binding.keyID)) {
						binding.execute(getMousePosition());
					}

				case InputStateType::MOUSE_MOTION:
					// this suck?
						binding.execute(getMousePosition());
					break;

					//doesn't work yet.
				case InputStateType::MOUSE_CLICK:
					if (wasKeyReleased(binding.keyID)) {
						binding.execute(getMousePosition());
					}
					break;
					//doesn't work yet.
				case InputStateType::MOUSE_DOUBLECLICK:
					if (wasKeyReleased(binding.keyID)) {
						binding.execute(getMousePosition());
					}
					break;

				default:
					break;
				}
			}
			for (InputBinding binding : m_keyboardBindings) {
				switch (binding.inputStateType)
				{
				case InputStateType::DOWN:
					if (isKeyDown(binding.keyID)) {
						binding.execute();
					}
					break;
				case InputStateType::UP:
					if (isKeyUp(binding.keyID)) {
						binding.execute();
					}
					break;
				case InputStateType::PRESSED:
					if (wasKeyPressed(binding.keyID)) {
						binding.execute();
					}
					break;
				case InputStateType::RELEASED:
					if (wasKeyReleased(binding.keyID)) {
						binding.execute();
					}
					break;
				default:
					break;
				}
			}
		}

		bool Input::shutdown() {

			m_keyboardBindings.clear();
			m_mouseBindings.clear();
			return true;
		}

		void Input::bindInput(InputBinding binding) {
			m_keyboardBindings.push_back(binding);
		}

		void Input::bindInput(MouseBinding binding)
		{
			m_mouseBindings.push_back(binding);
		}

		void Input::addInputComponent(IInput* component)
		{
			if(component != nullptr)
				m_inputComponents.push_back(component);
		}

		fmath::Vector2 Input::getMousePosition(bool previousFrame) const {
			return previousFrame ? m_oldMousePosition : m_currentMousePosition;
		}

		fmath::Vector2 Input::getMouseMovement() const {
			return fmath::Vector2(m_currentMousePosition.x - m_oldMousePosition.x, m_currentMousePosition.y - m_oldMousePosition.y);
		}

		bool Input::isMouseClicked(unsigned int keyID) const
		{
			return false;
		}

		bool Input::isMouseDoubleClicked(unsigned int keyID) const
		{
			return false;
		}

		bool Input::isKeyDown(unsigned int keyID) const {
			auto it = m_keyMap.find(keyID);
			if (it != m_keyMap.end()) {
				return it->second;
			}
			else {
				return false;
			}
		}

		bool Input::isKeyUp(unsigned int keyID) const {
			auto it = m_keyMap.find(keyID);
			if (it != m_keyMap.end()) {
				return !it->second;
			}
			else {
				return true;
			}
		}

		bool Input::wasKeyPressed(unsigned int keyID) const {
			return isKeyDown(keyID) && !wasKeyDown(keyID);
		}

		bool Input::wasKeyReleased(unsigned int keyID) const {
			return !isKeyDown(keyID) && wasKeyDown(keyID);
		}

		bool Input::wasKeyDown(unsigned int keyID) const {
			auto it = m_previousKeyMap.find(keyID);
			if (it != m_previousKeyMap.end()) {
				return it->second;
			}
			else {
				return false;
			}
		}
	}
}