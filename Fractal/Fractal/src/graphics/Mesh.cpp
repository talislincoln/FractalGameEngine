#include "graphics\Mesh.h"

namespace fractal {
	namespace fgraphics {
		Mesh::Mesh(std::vector<fgraphics::Vertex> vertices) : m_vertices(vertices) {//, m_size(0) {
			/*glGenBuffers(1, &m_vbo);
			m_size = m_vertices.size() * sizeof(fgraphics::Vertex);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			//orphan the buffer in order to increase speed (no need to rewrite to the same buffer - get a new one)
			glBufferData(GL_ARRAY_BUFFER, m_size,nullptr, GL_DYNAMIC_DRAW);
			//upload data
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_size, m_vertices.data());
			glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind the buffer*/
		}

		Mesh::~Mesh() {

		}

		/*void Mesh::draw() {
			if (m_vbo == 0) {
				glGenBuffers(1, &m_vbo);
			}

			if (m_vao == 0) {
				glGenVertexArrays(1, &m_vao);
			}
			glBindVertexArray(m_vao);

			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(fgraphics::Vertex), (void*)offsetof(fgraphics::Vertex, position));
			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(fgraphics::Vertex), 0);
			glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

			glDisableVertexAttribArray(0);
			glBindVertexArray(0);
		}*/
	}
}