#ifndef MESHSHADER_H
#define MESHSHADER_H

#include <Fractal\include\graphics\Program.h>
#include <GL\glew.h>
#include <string>
namespace fractal {
	namespace fgraphics {
		class MeshShader : public Shader {
		private:
			const GLchar* m_vertPath;
			const GLchar* m_fracPath;
		public:
			inline MeshShader(GLchar* vertPath = "res/shaders/vertexShader.txt", GLchar* fracPath = "res/shaders/fragmentShader.txt")
				:  Shader(vertPath, fracPath) , m_vertPath(vertPath), m_fracPath(fracPath){

			}

		};
	}
}
#endif // !meshShader_H
