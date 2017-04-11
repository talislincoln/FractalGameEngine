#include "InputManager.h"

fractal::InputManager::InputManager()
{
}

fractal::InputManager::~InputManager()
{
}

fKeyboardIndex fractal::InputManager::addKeyboardInput(IKeyboardInput * component)
{
	return fKeyboardIndex();
}

fMouseIndex fractal::InputManager::addMouseInput(IMouseInput * component)
{
	return fMouseIndex();
}
