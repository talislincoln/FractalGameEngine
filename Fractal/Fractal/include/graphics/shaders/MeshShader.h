#ifndef MESHSHADER_H
#define MESHSHADER_H

#include <Fractal\include\graphics\ShaderProgram.h>
#include <GL\glew.h>
namespace fractal {
	namespace fgraphics {
		class MeshShader : public ShaderProgram {
		private:
			const GLchar* m_vertPath = "res/shaders/vertexShader.txt";
			const GLchar* m_fracPath = "res/shaders/fragmentShader.txt";
			
		public:
			inline MeshShader() : ShaderProgram("res/shaders/vertexShader.txt", "res/shaders/fragmentShader.txt"){

			}

		};
	}
}
#endif // !meshShader_H
