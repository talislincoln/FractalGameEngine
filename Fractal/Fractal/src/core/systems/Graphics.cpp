#include "core\systems\Graphics.h"
#include "core\systems\Window.h"
#include "core\systems\manager\SystemManager.h"
#include "helpers\Singleton.h"

#include <GL\glew.h>
#include <iostream>

namespace fractal {
	namespace fcore {
		Graphics::Graphics() : 
			System(SystemType::GRAPHICS_SYSTEM),
			m_window(nullptr)
		{
			//empty
		}

		Graphics::~Graphics() {
			//empty
		}

		bool Graphics::initialize() {
			this->m_window = static_cast<Window*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::WINDOW_SYSTEM));
			
			//opengl context store all opengl related things such as buffers and so on
			SDL_GLContext glContext = SDL_GL_CreateContext(m_window->getSDLWindow());
			if (glContext == nullptr) {
				//Logger::log("erro creating window context");
				std::cerr << "Error creating window context\n" << std::endl;
				return false;
			}

			//init and setup glew with hardware
			GLenum error = glewInit();
			if (error != GLEW_OK) {
				//Logger::log("erro initializing glew in window");
				std::cerr << "Error initializing glew in window\n" << std::endl;
				return false;
			}

			glViewport(0, 0, WWIDTH, WHEIGHT);

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			//getting opengl current version 
			std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

			//;w; opengl options
			glFrontFace(GL_CCW); //;w; vertices need to be created in clock wise order or else the normals will make the images render the oppsite direction
			glCullFace(GL_BACK);

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_FRAMEBUFFER_SRGB);
			return true;
		}

		void Graphics::update() {
			//empty
		}

		void Graphics::draw() {
			// all should be draw here. 
			// draw should be in order of 
			/// shader program ( the material id?)
			/// texture
			/// vao

		}

		bool Graphics::shutdown() {
			return true;
		}

		void Graphics::beginDraw() {
			///;W; READING THE SHADER FILES FOR EACH MESH COMPONENT
			///;W; CLEARING THE SCREEN

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearDepth(1.0f);


			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT); // somewhere else 
			//get list of mesh need to be drawn
		}

		void Graphics::endDraw() {
			///;W; DESTROY EVERYTHING
			///;W; SWITCH BUFFERS
			//glDisable(GL_CULL_FACE);
			//glDisable(GL_DEPTH_TEST);
			//glDisable(GL_TEXTURE_2D);
			//glDisable(GL_FRAMEBUFFER_SRGB);

			//;w; switches buffers at the end
			SDL_GL_SwapWindow(m_window->getSDLWindow());
		}
	}
}