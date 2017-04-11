#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include "helpers\Manager.h"
#include "interfaces\IInput.h"
typedef unsigned int fMouseIndex;
typedef unsigned int fKeyboardIndex;

namespace fractal {
	class InputManager : public Manager {
	public:
		InputManager();
		virtual ~InputManager();
		fKeyboardIndex addKeyboardInput(IKeyboardInput* component);
		fMouseIndex addMouseInput(IMouseInput* component);
	private:

		fmath::Vector2 m_mouseCoordinates;
		std::vector<IMouseInput*> m_mouseInputComponents;
		std::vector<IKeyboardInput*> m_keyboardInputComponents;
	};
}


#endif // !INPUTMANAGER_H
