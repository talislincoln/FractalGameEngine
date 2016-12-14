#ifndef INPUTSTATETYPE_H
#define INPUTSTATETYPE_H

namespace fractal {
	enum class InputStateType {
		PRESSED,
		RELEASED,
		DOWN,
		UP,
		MOUSE_MOTION,
		MOUSE_CLICK
	};
}


#endif // !INPUTSTATETYPE_H
