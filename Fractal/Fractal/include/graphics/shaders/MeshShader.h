#ifndef MESHSHADER_H
#define MESHSHADER_H

#include <Fractal\include\graphics\ShaderProgram.h>
#include <GL\glew.h>

#define MESH_VERTEX_SHADER "res/shaders/vertexShader.txt"
#define MESH_FRAGMENT_SHADER "res/shaders/fragmentShader.txt"

namespace fractal {
	namespace fgraphics {
		class MeshShader : public ShaderProgram {
		public:
			UniformMatrix* view = new UniformMatrix("view");
			UniformMatrix* projectionMatrix = new UniformMatrix("projection");
			UniformMatrix* modelMatrix = new UniformMatrix("model");
			//UniformBoolean hasExtraMap = new UniformBoolean("hasExtraMap");
			UniformVector3* lightDirection = new UniformVector3("lightDirection");
			//UniformVec4 plane = new UniformVec4("plane");

			//UniformSampler diffuseMap = new UniformSampler("diffuseMap");
			//UniformSampler extraMap = new UniformSampler("extraMap");
			inline MeshShader() : ShaderProgram(MESH_VERTEX_SHADER, MESH_FRAGMENT_SHADER, 3, "position", "normal", "texCoord" ) {
				storeUniformLocations(3, view, projectionMatrix, modelMatrix);
			}
		};
	}
}
#endif // !meshShader_H
