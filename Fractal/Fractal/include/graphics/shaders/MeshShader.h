#ifndef MESHSHADER_H
#define MESHSHADER_H

#include <Fractal\include\graphics\ShaderProgram.h>
#include <GL\glew.h>

#define MESH_VERTEX_SHADER "res/shaders/vertexShader.txt"
#define MESH_FRAGMENT_SHADER "res/shaders/fragmentShader.txt"

namespace fractal {
	namespace fgraphics {
		class MeshShader : public ShaderProgram {
		private:
			inline void bindAttributes() {
				addAttrib("position");
				addAttrib("texCoord");
				addAttrib("normal");
			}
			
		public:
			inline MeshShader() : ShaderProgram(MESH_VERTEX_SHADER, MESH_FRAGMENT_SHADER){
				bindAttributes();
			}
		};
	}
}
#endif // !meshShader_H
