#ifndef _MESH_H
#define _MESH_H

#include "graphics\Vertex.h"
#include "scene\Component.h"
#include "interfaces\IDrawable.h"

#include <GL\glew.h>
#include <vector>

namespace fractal {
	namespace fgraphics {
		class Mesh  {
		public:
			Mesh(std::vector<fgraphics::Vertex> vertices);
			virtual ~Mesh();

			inline const std::vector<fgraphics::Vertex> getVertices() const {
				return m_vertices;
			}

		private:
			std::vector<fgraphics::Vertex> m_vertices;
		};
	}
}

#endif // !_MESH_H
