#ifndef _WINDOW_H
#define _WINDOW_H

#include "System.h"
#include "interfaces\IDrawable.h"

#include <string>
#include <SDL\SDL.h>

#define WTITLE "Fractal GE"
//;w; changed them a little
#define WWIDTH 1920
#define WHEIGHT 1080

/**
the parameters will hardcode for now, the idea is to read them all from a configuration file
*/

namespace fractal {
	namespace fcore {
		class Window : public System {
		public:
			Window();
			virtual ~Window();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			inline SDL_Window* getSDLWindow() { return m_Window; }
			inline int getWidth() { return m_width; }
			inline int getHeight() { return m_height; }
		private:
			int m_width; ///< Window width
			int m_height; ///< Window height

			std::string m_title; ///< Window title

			SDL_Window* m_Window; ///< Reference for the SDL_Window;
		};
	}
}

#endif