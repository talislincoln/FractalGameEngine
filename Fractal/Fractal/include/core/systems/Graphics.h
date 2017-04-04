#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "System.h"
#include "interfaces\IDrawable.h"
#include <GL\glew.h>

namespace fractal {
	namespace fcore {
		class Window;

		class Graphics : public System, public IDrawable {
		public:
			Graphics();
			virtual ~Graphics();

			virtual bool initialize();
			virtual void update();
			virtual void draw();
			virtual bool shutdown();

			void beginDraw();
			void endDraw();

		private:
			Window *m_window;

			// Shaders
		};
	}
}
#endif // !_GRAPHICS_H
