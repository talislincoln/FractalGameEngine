#include "graphics\Vao.h"
#include "graphics\MeshData.h"
namespace fractal{
	namespace fgraphics {
		const GLuint Vao::create()
		{
			GLuint m_vao;
			printf("creating VAO \n");
			glGenVertexArrays(1, &m_vao);
			return m_vao;
		}
		Vao::Vao() : vao(create())
		{
		}
		void Vao::bind()
		{
			glBindVertexArray(vao);
		}
		void Vao::unbind()
		{

			glBindVertexArray(0);
		}
		void Vao::loadMeshIntoOpenGL(MeshData * meshData)
		{
			furthestPoint = meshData->getFurthestPoint();
			loadMeshIntoOpenGL(meshData->getVertices(), meshData->getNormals(), meshData->getTextureCoords(), meshData->getIndices());
			meshData->destroy();
			meshData = nullptr;
		}
		void Vao::loadMeshIntoOpenGL(const std::vector<fmath::Vector3>& positions
			, const std::vector<fmath::Vector3>& normals, const std::vector<fmath::Vector2>& UVs, const std::vector<int>& indices)
		{
			indicesSize = indices.size();
			vecticesSize = positions.size();
			bind();
			// magic~
			//make vector into class* by doing &class[0]. then make Vector3* into float* by doing *(Vector3)
			loadVboIntoOpenGL(GL_ARRAY_BUFFER, &(positions[0]), vecticesSize, 3);
			loadVboIntoOpenGL(GL_ARRAY_BUFFER, &(normals[0]), vecticesSize, 3);
			loadVboIntoOpenGL(GL_ARRAY_BUFFER, &UVs[0], vecticesSize, 2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			loadIndexIntoOpenGL(GL_ELEMENT_ARRAY_BUFFER, &indices[0], indices.size());

			unbind();
		}
		void Vao::loadUIIntoOpenGL(const std::vector<fmath::Vector2>& position)
		{
			bind();

			unbind();
		}
		void Vao::loadVboIntoOpenGL(const GLuint type,const void* data, size_t size, size_t Dimension)
		{
			GLuint vbo = 0;
			glGenBuffers(1, &vbo);

			//start using this vbo
			glBindBuffer(type, vbo);
			glBufferData(type, size * Dimension * sizeof(GL_FLOAT), data, GL_STATIC_DRAW);

			// the meaning of each attribute
			// 1 - attribute position
			// 2 - the size of the array (3 because we only have x,y,z for now
			// 3 - the type of the data being passed in
			// 4 - if the data is normalized
			// 5 - distance between each vertices
			glVertexAttribPointer(vbos.size(), Dimension, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			vbos.push_back(vbo);
		}
		void Vao::loadIndexIntoOpenGL(const GLuint type, const int* data, size_t size)
		{
			GLuint vbo = 0;
			glGenBuffers(1, &vbo);
			vbos.push_back(vbo);
			//start using this vbo
			glBindBuffer(type, vbo);
			glBufferData(type, size * sizeof(GL_UNSIGNED_INT), data, GL_STATIC_DRAW);
		}
		void Vao::destroy()
		{
			glDeleteVertexArrays(1, &vao);

			for (GLuint& vbo : vbos) {
				glDeleteBuffers(1, &vbo);
			}

			vbos.clear();

		}
	}
}