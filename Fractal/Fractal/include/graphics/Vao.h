#ifndef VAO_H
#define VAO_H
#include <GL\glew.h>
#include <vector>
#include <FractalMath\Math.h>
namespace fractal {
	namespace fgraphics {
		class MeshData;
		class Vao {
		public:
			Vao();
			const GLuint VAO;
			size_t indicesSize, vecticesSize;
			GLfloat  furthestPoint;

			std::vector<GLuint> vbos;
			void bind();
			void unbind();
			void loadMeshIntoOpenGL(MeshData* meshData);
			void loadMeshIntoOpenGL(const std::vector<fmath::Vector3>& positions,
				const std::vector<fmath::Vector3>& normals, const std::vector<fmath::Vector2>& UVs, const std::vector<int>& indices);
			void loadUIIntoOpenGL();
			void loadSkybox();
			void destroy();
		private:
			void loadVboIntoOpenGL(const GLuint type, const void* data, size_t size, size_t dimension);
			void loadIndexIntoOpenGL(const GLuint type, const int* position, size_t size);
			static const GLuint create();
		};
	}
}

#endif // !VAO_H
