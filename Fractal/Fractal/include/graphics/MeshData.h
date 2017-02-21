#ifndef MESH_DATA_H
#define MESH_DATA_H


#include <Fractal\include\graphics\Vertex.h>
#include <FractalMath\Vector.h>
namespace fractal {
	namespace fgraphics {
		class MeshData {
		private:
			static const int DIMENSIONS = 3;
			
			std::vector<fgraphics::Vertex> m_vertices;
			std::vector<fmath::Vector2> m_textureCoords;
			std::vector<fmath::Vector3> m_normals;
			std::vector<int>   m_indices;
			float  m_furthestPoint;
			size_t m_size;

		public:

			MeshData(const MeshData&) = delete;
			MeshData(MeshData&&) = delete;
			MeshData& operator=(const MeshData&) = delete;
			MeshData& operator=(MeshData&&) = delete;

			MeshData(std::vector<fgraphics::Vertex> vertices, std::vector<fmath::Vector2> textureCoords, std::vector<fmath::Vector3> normals,
				std::vector<int> indices, float furthestPoint, int size) :
				m_vertices(vertices), m_textureCoords(textureCoords), m_normals(normals), 
				m_indices(indices), m_furthestPoint(furthestPoint), m_size(size){
			}

			inline size_t getVertexCount() {
				return m_size;
			}

			inline std::vector<fmath::Point3> getVertices() {
				std::vector<fmath::Point3> temp;
				for (fgraphics::Vertex it : m_vertices) {
					temp.push_back(it.getPosition());
				}
				return temp;
			}

			inline std::vector<fmath::Vector2> getTextureCoords() {
				return m_textureCoords;
			}

			inline std::vector<fmath::Vector3> getNormals() {
				return m_normals;
			}

			inline std::vector<int> getIndices() {
				return m_indices;
			}

			inline float getFurthestPoint() {
				return m_furthestPoint;
			}

		};

	}
}
#endif // !MESH_DATA_H