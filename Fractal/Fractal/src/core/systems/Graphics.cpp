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
			this->m_window = dynamic_cast<Window*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::WINDOW_SYSTEM));

			//opengl context store all opengl related things such as buffers and so on
			SDL_GLContext glContext = SDL_GL_CreateContext(m_window->getSDLWindow());
			if (glContext == nullptr) {
				//Logger::log("erro creating window context");
				std::cerr << "Error creating window context\n" << std::endl;
				return false;
			}

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

			///;W; ERASE?
			//// **** COMPILING SHADERS
			//// Vertex shader
			//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
			//glCompileShader(vertexShader);
			//// Check for compile time errors
			//GLint success;
			//GLchar infoLog[512];
			//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			//if (!success)
			//{
			//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			//}
			//// Fragment shader
			//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
			//glCompileShader(fragmentShader);
			//// Check for compile time errors
			//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			//if (!success)
			//{
			//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			//}
			//// Link shaders
			//shaderProgram = glCreateProgram();
			//glAttachShader(shaderProgram, vertexShader);
			//glAttachShader(shaderProgram, fragmentShader);
			//glLinkProgram(shaderProgram);
			//// Check for linking errors
			//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			//if (!success) {
			//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			//}
			//glDeleteShader(vertexShader);
			//glDeleteShader(fragmentShader);
			//// ***** ENDING SHADER COMPILATION

			//;w; opengl options
			glFrontFace(GL_CW); //;w; vertices need to be created in clock wise order or else the normals will make the images render the oppsite direction
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_FRAMEBUFFER_SRGB);

			return true;
		}

		void Graphics::update() {
			//empty
		}

		void Graphics::draw() {
		}

		bool Graphics::shutdown() {
			return true;
		}

		void Graphics::beginDraw() {
			///;W; READING THE SHADER FILES FOR EACH MESH COMPONENT
			///;W; CLEARING THE SCREEN
			glUseProgram(shaderProgram);

			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT); // somewhere else 
			//get list of mesh need to be drawn
		}

		void Graphics::endDraw() {
			///;W; DESTROY EVERYTHING
			///;W; SWITCH BUFFERS
			//;w; delete/unbind vao, vbo, ebo


			//;w; switches buffers at the end
			SDL_GL_SwapWindow(m_window->getSDLWindow());
		}
	}
}