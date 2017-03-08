#include "graphics\Mesh.h"
#include "helpers\Singleton.h"
#include "scene\components\MeshComponent.h"
#include "core\systems\Window.h"
#include "core\systems\manager\SystemManager.h"
#include "graphics\ShaderProgram.h"
#include <FractalMath\Matrix.h>
#include "scene\GameObject.h"
#include "scene\components\TransformComponent.h"
#include <assert.h>

#include <Fractal\include\core\systems\manager\CameraManager.h>
#include <Fractal\include\scene\objects\CameraObject.h>

namespace fractal {
	namespace fscene {
		using namespace fmath;
		MeshComponent::MeshComponent(fgraphics::MeshData* mesh) : 
			Component("MeshComponent"), 
			m_mesh(mesh),
			m_shader(new fgraphics::MeshShader()), 
			m_texture(fgraphics::Texture::newTexture("res/images/awesome.png").create())
		{
			//empty
		}

		MeshComponent::~MeshComponent() {
			//empty
		}

		bool MeshComponent::initialize() {
			createVAO();
			storeDataInVAO();
			bindIndicesBuffer();
			unbindVAO();

			return true;
		}

		void MeshComponent::draw() {
			glBindVertexArray(m_vao);

			m_shader->use();// all this is going into Materials
			m_texture->bindToUnit(0);

			fscene::CameraObject* camera = fhelpers::Singleton<fcore::CameraManager>::getInstance().getActiveCamera();

			//m_shader->view->loadMatrix(fmath::Matrix4::translate(Vector3(0.0f, test -= 0.00001f, -10.0f)));
			m_shader->view->loadMatrix(camera->getComponent<TransformComponent>()->getWorldMatrix());
			m_shader->projectionMatrix->loadMatrix(fmath::Matrix4::perspective(45.0f, 800.0f / 500.0f, 0.1f, 100.0f)); // camera matrix = projection * view

			m_shader->modelMatrix->loadMatrix(this->getParent()->getComponent<TransformComponent>()->getWorldMatrix());

			//glDrawArrays(GL_TRIANGLES, 0, m_mesh->getVertices().size());
			glDrawElements(GL_TRIANGLES, m_mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			
			m_shader->unuse();
		}

		void MeshComponent::update() {
		}

		bool MeshComponent::shutdown() {
			glDeleteVertexArrays(1, &m_vao);

			for (GLuint& vbo : m_vbos) {
				glDeleteBuffers(1, &vbo);
			}
			
			m_vbos.clear();

			m_shader->destroy();
			delete m_shader;
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

			glBufferData(GL_ARRAY_BUFFER, m_mesh->getVertices().size() * sizeof(fmath::Vector3), &(m_mesh->getVertices()[0]), GL_STATIC_DRAW);
			//TODO:: need to store texture and normal data too.

			// the meaning of each attribute
			// 1 - attribute position
			// 2 - the size of the array (3 because we only have x,y,z for now
			// 3 - the type of the data being passed in
			// 4 - if the data is normalized
			// 5 - distance between each vertices
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
			//unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// TODO: I AM DONE WITH MESHDATA!
			//m_mesh->destroy();
			//delete m_mesh;
		}

		void MeshComponent::unbindVAO() const {
			glBindVertexArray(0);
		}

		void MeshComponent::bindIndicesBuffer() {
			GLuint vbo = 0;
			glGenBuffers(1, &vbo);
			m_vbos.push_back(vbo);


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
			
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh->getIndices().size() * sizeof(GL_INT), &(m_mesh->getIndices()[0]), GL_STATIC_DRAW);
		}
	}
}