#ifndef _WINDOW_H
#define _WINDOW_H

#include "System.h"
#include "interfaces\IDrawable.h"

#include <string>
#include <SDL\SDL.h>

#define WTITLE "Fractal GE"
#define WWIDTH 600
#define WHEIGHT 480

/**
the parameters will hardcode for now, the idea is to read them all from a configuration file
*/

namespace fractal {
	namespace fcore {
		class Window : public System, public IDrawable {
		public:

			Window();
			virtual ~Window();

			virtual bool initialize();
			virtual void update();
			virtual void draw();
			virtual bool shutdown();


		private:
			int m_width; ///< Window width
			int m_height; ///< Window height

			std::string m_title; ///< Window title

			SDL_Window* m_Window; ///< Reference for the SDL_Window;
		};
	}
}

#endif