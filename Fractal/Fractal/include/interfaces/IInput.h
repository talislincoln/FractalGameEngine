#ifndef IINPUT_H
#define IINPUT_H
#include <FractalMath\Vector.h>
#include "core\systems\Input.h"
namespace fractal {
	class IInput {
	public:
		virtual void keyPressed(unsigned int key) {}
		virtual void keyReleased(unsigned int key) {}
		virtual void keyDown(unsigned int key) {}
		virtual void keyUp(unsigned int key) {}

		virtual void mousePressed(unsigned int key, const fmath::Vector2& mouseCoord) {}
		virtual void mouseReleased(unsigned int key, const fmath::Vector2& mouseCoord) {}
		virtual void mouseDown(unsigned int key, const fmath::Vector2& mouseCoord) {}
		virtual void mouseUp(unsigned int key, const fmath::Vector2& mouseCoord) {}

		virtual void setupInput(fcore::Input* input) = 0;
	};
}

#endif // !IINPUT_H
