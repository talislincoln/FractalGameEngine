#include "graphics\Mesh.h"

namespace fractal {
	namespace fgraphics {
		Mesh::Mesh(std::vector<fgraphics::Vertex> vertices) : m_vertices(vertices) {
		}

		Mesh::~Mesh() {
		}
	}
}