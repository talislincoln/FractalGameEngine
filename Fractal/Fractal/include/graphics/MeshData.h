#pragma once
#include <Fractal\include\graphics\Vertex.h>
#include <FractalMath\Vector.h>
namespace fractal {
	namespace fgraphics {
		class MeshData {
		private:
			static const int DIMENSIONS = 3;
			
			std::vector<fmath::Point3> m_vertices;
			std::vector<fmath::Vector2> m_textureCoords;
			std::vector<fmath::Vector3> m_normals;
			std::vector<int>   m_indices;
			float  m_furthestPoint;
			int m_size;

		public:

			MeshData(const MeshData&) = delete;
			MeshData(MeshData&&) = delete;
			MeshData& operator=(const MeshData&) = delete;
			MeshData& operator=(MeshData&&) = delete;

			MeshData(std::vector<fmath::Point3> vertices, std::vector<fmath::Vector2> textureCoords, std::vector<fmath::Vector3> normals,
				std::vector<int> indices, float furthestPoint, int size) :
				m_vertices(vertices), m_textureCoords(textureCoords), m_normals(normals), 
				m_indices(indices), m_furthestPoint(furthestPoint), m_size(size){
			}

			inline int getVertexCount() {
				return m_size / DIMENSIONS;
			}

			inline std::vector<fmath::Point3> getVertices() {
				return m_vertices;
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