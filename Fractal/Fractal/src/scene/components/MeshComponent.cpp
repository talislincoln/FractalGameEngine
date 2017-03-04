#include "graphics\Mesh.h"
#include "helpers\Singleton.h"
#include "scene\components\MeshComponent.h"
#include "core\systems\Window.h"
#include "core\systems\manager\SystemManager.h"
#include "graphics\ShaderProgram.h"
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
			shader->addAttrib("position");
			shader->addAttrib("texCoord");
			shader->addAttrib("normal");
		}

		MeshComponent::~MeshComponent() {

		}

		bool MeshComponent::initialize() {
			createVAO();
			bindIndicesBuffer();
			storeDataInVAO();
			unbindVAO();

			return true;
		}

		void MeshComponent::draw() {
			shader->use();
			glBindVertexArray(m_vao);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			fmath::Matrix4 transformationMatrix = getParent()->getComponent<TransformComponent>()->getWorldMatrix();

			//glDrawArrays(GL_TRIANGLES, 0, m_mesh->getVertices().size());
			glDrawElements(GL_TRIANGLES, m_mesh->getVertices().size(), GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(0);
			glBindVertexArray(0);
			shader->unuse();
		}

		void MeshComponent::update() {
		}

		bool MeshComponent::shutdown() {
			glDeleteVertexArrays(1, &m_vao);

			for (GLuint& vbo : m_vbos) {
				glDeleteBuffers(1, &vbo);
			}
			
			m_vbos.clear();

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
			GLuint vbo = 0;
			glGenBuffers(1, &vbo);
			m_vbos.push_back(vbo);

			//start using this vbo
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

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

		void MeshComponent::unbindVAO() const {
			glBindVertexArray(0);
		}

		void MeshComponent::bindIndicesBuffer() {
			GLuint vbo = 0;
			glGenBuffers(1, &vbo);
			m_vbos.push_back(vbo);


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
			
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh->getIndices().size() * sizeof(GL_INT), &m_mesh->getIndices()[0], GL_STATIC_DRAW);
		}
	}
}