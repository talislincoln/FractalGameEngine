#include "core\systems\Window.h"

#include <iostream>

namespace fractal {
	namespace fcore {
		Window::Window() :
			System(SystemType::WINDOW_SYSTEM), //init parent
			m_width(WWIDTH), m_height(WHEIGHT), m_title(WTITLE)
		{
			//empty
		}

		Window::~Window() {
			//empty
		}

		bool Window::initialize() {
			std::cout << "Initializing SDL window" << std::endl;

			Uint32 flags = SDL_WINDOW_OPENGL;

			//we can create different flags for the different types of windows
			/*if (m_Flags & INVISIBLE) {
				flags |= SDL_WINDOW_HIDDEN;
			}

			if (m_Flags & FULLSCREEN) {
				flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
			}

			if (m_Flags & BORDLESS) {
				flags |= SDL_WINDOW_BORDERLESS;
			}*/

			m_Window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, flags);

			if (m_Window == nullptr) {
				//Logger::log("erro creating SDL_Window");
				std::cerr << "erro creating SDL_Window" << std::endl;
				return false;
			}

			return true;
		}

		void Window::update() {
			//empty
		}

		bool Window::shutdown() {
			if (m_Window != nullptr) {
				SDL_DestroyWindow(m_Window);
				m_Window = nullptr;

				return true;
			}
			
			//return false if error
			printf("SDL_DestroyWindow failed: %s\n", SDL_GetError());
			return false;
		}
	}
}