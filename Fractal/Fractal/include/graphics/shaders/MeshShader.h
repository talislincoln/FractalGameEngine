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
			UniformMatrix* view;
			UniformMatrix* projectionMatrix;
			UniformMatrix* modelMatrix;
			//UniformBoolean hasExtraMap = new UniformBoolean("hasExtraMap");
			UniformVector3* lightDirection;
			//UniformVec4 plane = new UniformVec4("plane");

			UniformSampler* diffuseMap;
			//UniformSampler extraMap = new UniformSampler("extraMap");
			inline MeshShader() : ShaderProgram(MESH_VERTEX_SHADER, MESH_FRAGMENT_SHADER, 3, "position", "normal", "texCoord" ),
			view(new UniformMatrix("view")), projectionMatrix(new UniformMatrix("projection")), modelMatrix(new UniformMatrix("model"))
			, lightDirection ( new UniformVector3("lightDirection")), diffuseMap (new UniformSampler("diffuseMap")){
				storeUniformLocations(4, view, projectionMatrix, modelMatrix, diffuseMap);
				loadTexture();
			}
			inline void loadTexture() {
				diffuseMap->loadTextureUnit(0);
			}
			inline void destroy() {
				delete view;
				delete projectionMatrix;
				delete modelMatrix;
				delete lightDirection;
				delete diffuseMap;
			}
		};
	}
}
#endif // !meshShader_H
