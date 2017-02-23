#ifndef _VERTEX_H
#define _VERTEX_H
#include <FractalMath\Vector.h>
#include <string>
#include <vector>

namespace fractal {
	namespace fgraphics {
		//??
		struct Texture {
			unsigned int id;
			std::string type;
		};

		struct Colour {
			int r;
			int g;
			int b;
			int a;
			Colour(int r = 0, int g = 0, int b = 0, int a = 1) : r(r), g(g), b(b), a(a) {}


			inline Colour& operator= (const Colour& other) {
				this->r = other.r;
				this->g = other.g;
				this->b = other.b;
				this->a = other.a;
				return *this;
			}

		};
		struct Vertex {
			fmath::Point3 position;
			static const int NO_INDEX = -1;
			int m_textureIndex = NO_INDEX;
			int m_normalIndex = NO_INDEX;
			Vertex* m_duplicateVertex = nullptr;
			int m_index;
			float m_length;
			std::vector<fmath::Vector3> m_tangents;
			fmath::Vector3 m_averagedTangent;
			Colour colour;

			Vertex(fmath::Point3 p = fmath::Point3(), int _index = 0, Colour colour = Colour()) : position(p), m_index(_index), colour(colour) {}

			 inline void addTangent(fmath::Vector3 tangent) {
				m_tangents.push_back(tangent);
			}
			 inline void averageTangents() {
				if (m_tangents.empty()) {
					return;
				}
				for (fmath::Vector3 tangent : m_tangents) {
					m_averagedTangent += tangent + m_averagedTangent;
				}
				m_averagedTangent.normalize();
			}
			 inline fmath::Vector3 getAverageTangent() {
				return m_averagedTangent;
			}
			 inline int getIndex() {
				return m_index;
			}
			 inline float getLength() {
				return m_length;
			}
			 inline bool isSet() {
				return m_textureIndex != NO_INDEX && m_normalIndex != NO_INDEX;
			}
			 inline bool hasSameTextureAndNormal(int m_textureIndexOther, int m_normalIndexOther) {
				return m_textureIndexOther == m_textureIndex && m_normalIndexOther == m_normalIndex;
			}
			 inline void setTextureIndex(int m_textureIndex) {
				 this->m_textureIndex = m_textureIndex;
			}
			 inline void setNormalIndex(int m_normalIndex) {
				this->m_normalIndex = m_normalIndex;
			}
			 inline fmath::Vector3 getPosition() {
				return position;
			}
			 inline int getTextureIndex() {
				return m_textureIndex;
			}
			 int getNormalIndex() {
				return m_normalIndex;
			}
			 inline Vertex* getDuplicateVertex() {
				return m_duplicateVertex;
			}
			 inline void setDuplicateVertex(Vertex* m_duplicateVertex) {
				this->m_duplicateVertex = m_duplicateVertex;
			}
			inline Vertex& operator= (const Vertex& other) {
				this->m_textureIndex = other.m_textureIndex;
				this->m_normalIndex = other.m_normalIndex;
				this->m_duplicateVertex = other.m_duplicateVertex;
				this->m_index = other.m_index;
				this->m_length = other.m_length;
				this->m_tangents = other.m_tangents;
				this->m_averagedTangent = other.m_averagedTangent;
				return *this;
			 }
		};
	}
}

#endif // !_VERTEX_H