#include "graphics\Mesh.h"

namespace fractal {
	namespace fgraphics {
		Mesh::Mesh(std::vector<fmath::Point3> vertices) : m_vertices(vertices) {
		}

		Mesh::~Mesh() {
		}
	}
}