#ifndef _INPUT_H
#define _INPUT_H

#include <Fractal\include\core\systems\System.h>
#include <Fractal\include\defines\InputStateType.h>

#include <SDL\SDL.h>

#include <unordered_map>
#ifndef _FUNCTIONAL_
#include <functional>
#endif

#ifndef _VECTOR_H

#endif // !_VECTOR_H

#include <FractalMath\Vector.h>

namespace fractal {
	class IInput;
	namespace fcore {
		struct InputBinding {
			InputBinding(unsigned int keyID, std::function<void()> fn, InputStateType inputState) :
				keyID(keyID), callbackFunction(fn), inputStateType(inputState)
			{
				//empty
			}

			InputBinding(const InputBinding& inputBinding) :
				keyID(inputBinding.keyID), callbackFunction(inputBinding.callbackFunction),
				inputStateType(inputBinding.inputStateType)
			{
				//empty
			}
			InputBinding operator= (const InputBinding& ref) {
				this->keyID = ref.keyID;
				this->callbackFunction = ref.callbackFunction;
				this->inputStateType = ref.inputStateType;
			}

			void execute() {
				callbackFunction();
			}

			unsigned int keyID;
			std::function<void()> callbackFunction;
			InputStateType inputStateType;
		};

		struct MouseBinding {
			MouseBinding(unsigned int keyID, std::function<void(const fmath::Vector2&)> fn, InputStateType inputState) :
				keyID(keyID), callbackFunction(fn), inputStateType(inputState)
			{
				//empty
			}

			MouseBinding(const MouseBinding& inputBinding) :
				keyID(inputBinding.keyID), callbackFunction(inputBinding.callbackFunction),
				inputStateType(inputBinding.inputStateType)
			{
				//empty
			}
			MouseBinding operator= (const MouseBinding& ref) {
				this->keyID = ref.keyID;
				this->callbackFunction = ref.callbackFunction;
				this->inputStateType = ref.inputStateType;
			}

			void execute(const fmath::Vector2& mousePosition) {
				callbackFunction(mousePosition);
			}

			unsigned int keyID;
			std::function<void(const fmath::Vector2&)> callbackFunction;
			InputStateType inputStateType;
		};

		class Input : public System {
		public:
			Input();
			virtual ~Input();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			//bool GetKey(unsigned int keyID);

			void bindInput(InputBinding binding);
			void bindInput(MouseBinding binding);

			void addInputComponent(IInput* component);
			/**
			\brief Get the mouse position.
			\param previousFrame If true, returns the mouse position on the last frame
			*/
			fmath::Vector2 getMousePosition(bool previousFrame = false) const;
			fmath::Vector2 getMouseMovement() const;
			bool isMouseClicked(unsigned int keyID) const;
			bool isMouseDoubleClicked(unsigned int keyID) const;

			bool isKeyDown(unsigned int keyID) const;
			bool isKeyUp(unsigned int keyID) const;
			bool wasKeyPressed(unsigned int keyID) const;
			bool wasKeyReleased(unsigned int keyID) const;

		private:
			inline void pressKey(unsigned int keyID) { m_keyMap[keyID] = true; }
			inline void releaseKey(unsigned int keyID) { m_keyMap[keyID] = false; }

			bool wasKeyDown(unsigned int keyID) const;

			std::unordered_map<unsigned int, bool> m_keyMap;
			std::unordered_map<unsigned int, bool> m_previousKeyMap;

			std::vector<InputBinding> m_keyboardBindings;
			std::vector<MouseBinding> m_mouseBindings;

			std::vector<IInput*> m_inputComponents;
			fmath::Vector2 m_mouseCoordinates;

			fmath::Vector2 m_currentMousePosition;
			fmath::Vector2 m_oldMousePosition;
		};
	}
}

#endif // !_INPUT_H
