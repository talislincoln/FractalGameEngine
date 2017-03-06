#ifndef _MESH_H
#define _MESH_H

#include <Fractal\include\graphics\Vertex.h>
#include <Fractal\include\scene\Component.h>
#include <Fractal\include\interfaces\IDrawable.h>

#include <GL\glew.h>
#include <vector>

namespace fractal {
	namespace fgraphics {
		class Mesh  {
		public:
			Mesh(std::vector<fmath::Point3> vertices);
			virtual ~Mesh();

			inline const std::vector<fmath::Point3> getVertices() const {
				return m_vertices;
			}

		private:
			std::vector<fmath::Point3> m_vertices;
			GLuint* indices;
			//std::vector<fgraphics::Vertex> m_vertices;
			//GLuint* indices;
		};
	}
}

#endif // !_MESH_H
