#ifndef MESH_DATA_H
#define MESH_DATA_H


#include <Fractal\include\graphics\Vertex.h>
#include <FractalMath\Vector.h>
namespace fractal {
	namespace fgraphics {
		class MeshData {
		private:
			static const int DIMENSIONS = 3;
			
			std::vector<fmath::Vector3> m_vertices;
			std::vector<fmath::Vector2> m_textureCoords;
			std::vector<fmath::Vector3> m_normals;
			std::vector<int>   m_indices;
			float  m_furthestPoint;

		public:

			MeshData(const MeshData&) = delete;
			MeshData(MeshData&&) = delete;
			MeshData& operator=(const MeshData&) = delete;
			MeshData& operator=(MeshData&&) = delete;

			MeshData(std::vector<fmath::Vector3> vertices, std::vector<fmath::Vector2> textureCoords, std::vector<fmath::Vector3> normals,
				std::vector<int> indices, float furthestPoint, int size) :
				m_vertices(vertices), m_textureCoords(textureCoords), m_normals(normals), 
				m_indices(indices), m_furthestPoint(furthestPoint){
			}

			inline size_t getVertexCount() {
				return m_vertices.size();
			}

			inline const std::vector<fmath::Vector3> getVertices() const {
				return m_vertices;
			}

			inline const std::vector<fmath::Vector2>& getTextureCoords() const{
				return m_textureCoords;
			}

			inline const std::vector<fmath::Vector3>& getNormals() const{
				return m_normals;
			}

			inline const std::vector<int>& getIndices() const {
				return m_indices;
			}

			inline const float& getFurthestPoint() const{
				return m_furthestPoint;
			}

		};

	}
}
#endif // !MESH_DATA_H