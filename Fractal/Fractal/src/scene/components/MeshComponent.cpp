#include "graphics\Mesh.h"
#include "helpers\Singleton.h"
#include "scene\components\MeshComponent.h"
#include "core\systems\Window.h"
#include "core\systems\manager\SystemManager.h"

#include <assert.h>

namespace fractal {
	namespace fscene {
		MeshComponent::MeshComponent(fgraphics::Mesh* mesh) : m_mesh(mesh) {

			std::vector<fgraphics::Vertex> vertices = mesh->getVertices();

			//generating array and buffer
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo);
			
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(fgraphics::Vertex), &vertices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(fgraphics::Vertex), (GLvoid*)0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		MeshComponent::~MeshComponent() {

		}

		/**
		Init the mesh component.
		*/
		bool MeshComponent::initialize() {
			
			return m_mesh != nullptr;
		}

		/**
		draw the mesh components based on the vertices provided.
		*/
		void MeshComponent::draw() {
			
			//binding vertex array
			glBindVertexArray(m_vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			//unbinding vertex array
			glBindVertexArray(0);
		}

		void MeshComponent::update() {

		}

		bool MeshComponent::shutdown() {
			//cleaning the buffers and array within the gpu
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_vbo);
			return true;
		}
	}
}
