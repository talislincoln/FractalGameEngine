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
			const GLchar* vertexShaderSource = "#version 330 core\n"
				"layout (location = 0) in vec3 position;\n"
				"void main()\n"
				"{\n"
				"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
				"}\0";
			const GLchar* fragmentShaderSource = "#version 330 core\n"
				"out vec4 color;\n"
				"void main()\n"
				"{\n"
				"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\n\0";

			GLuint shaderProgram;
			
		};
	}
}
#endif // !_GRAPHICS_H
