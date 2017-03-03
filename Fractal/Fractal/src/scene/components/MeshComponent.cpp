#include "graphics\Mesh.h"
#include "helpers\Singleton.h"
#include "scene\components\MeshComponent.h"
#include "core\systems\Window.h"
#include "core\systems\manager\SystemManager.h"
#include "graphics\Program.h"
//#include "scene\objects\FreeCamera.h"
#include <FractalMath\Matrix.h>
#include <SOIL\SOIL.h>
#include "scene\GameObject.h"
#include "scene\components\TransformComponent.h"

#include <assert.h>

namespace fractal {
	namespace fscene {
		using namespace fmath;
		MeshComponent::MeshComponent(fgraphics::MeshData* mesh) : 
			Component("MeshComponent"), m_mesh(mesh) {
			shader = new fgraphics::MeshShader();
			
		}

		MeshComponent::~MeshComponent() {

		}

		bool MeshComponent::initialize() {
			createVAO();
			storeDataInVAO();
			unbindVAO();

			return true;
		}

		void MeshComponent::draw() {
			glBindVertexArray(m_vao);
			glEnableVertexAttribArray(0);
			glDrawArrays(GL_TRIANGLES, 0, m_mesh->getVertexCount());
			glDisableVertexAttribArray(0);
			glBindVertexArray(0);
		}

		void MeshComponent::update() {
		}

		bool MeshComponent::shutdown() {
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_vbo);
			shader->destroy();
			delete shader;
			return true;
		}

		void MeshComponent::createVAO() {
			//first argument specifies the number of arrays to generate
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);
		}

		void MeshComponent::storeDataInVAO() {
			//create 1 vbo
			glGenBuffers(1, &m_vbo);

			//start using this vbo
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			glBufferData(GL_ARRAY_BUFFER, m_mesh->getVertices().size() * 3 * sizeof(GL_FLOAT), &m_mesh->getVertices()[0], GL_STATIC_DRAW);

			// the meaning of each attribute
			// 1 - attribute position
			// 2 - the size of the array (3 because we only have x,y,z for now
			// 3 - the type of the data being passed in
			// 4 - if the data is normalized
			// 5 - distance between each vertices
			// 6 - offset (should it start at the begining of the data
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			//unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void MeshComponent::unbindVAO() {
			glBindVertexArray(0);
		}
	}
}