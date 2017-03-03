#ifndef MESHSHADER_H
#define MESHSHADER_H

#include <Fractal\include\graphics\Program.h>
#include <GL\glew.h>
namespace fractal {
	namespace fgraphics {
		class MeshShader : public Shader {
		private:
			const GLchar* m_vertPath = "res/shaders/vertexShader.txt";
			const GLchar* m_fracPath = "res/shaders/fragmentShader.txt";
			
		public:
			inline MeshShader() : Shader(m_vertPath, m_fracPath){

			}

		};
	}
}
#endif // !meshShader_H
