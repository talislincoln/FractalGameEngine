#include "core\systems\Window.h"

#include <iostream>
#include <GL\glew.h>

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

			//opengl context store all opengl related things such as buffers and so on
			SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);
			if (glContext == nullptr) {
				//Logger::log("erro creating window context");
				std::cerr << "erro creating window context" << std::endl;
				return false;
			}

			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

			//init and setup glew with hardware
			GLenum error = glewInit();
			if (error != GLEW_OK) {
				//Logger::log("erro initializing glew in window");
				std::cerr << "erro initializing glew in window" << std::endl;
				return false;
			}

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			//getting opengl current version 
			std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

			//set vsync off
			//SDL_GL_SetSwapInterval(0);

			//enable alpha blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//SDL_GL_DeleteContext(glContext);

			return true;
		}

		void Window::update() {

			//printf("updating window\n");
		}

		void Window::draw() {
			//printf("drawing window\n");
			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			SDL_GL_SwapWindow(m_Window);
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