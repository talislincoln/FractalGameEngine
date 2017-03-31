#include "scene\components\MeshComponent.h"

#include "helpers\Singleton.h"
#include "scene\components\TransformComponent.h"
#include "core\systems\manager\SystemManager.h"
#include <FractalMath\Matrix.h>
#include "scene\GameObject.h"
#include <assert.h>

#include <Fractal\include\core\systems\manager\CameraManager.h>
#include <Fractal\include\scene\objects\CameraObject.h>
namespace fractal {
	namespace fscene {
		using namespace fmath;
		MeshComponent::MeshComponent(fgraphics::MeshData* mesh, fgraphics::Material* m) : 
			Component("MeshComponent"), 
			m_mesh(mesh),
			m_material(m)
		{
			//empty
		}

		MeshComponent::~MeshComponent() {
			//empty
		}

		bool MeshComponent::initialize() {
			m_indicesSize = m_mesh->getIndices().size();
			m_vecticesSize = m_mesh->getVertexCount();
			createVAO();
			storeDataInVAO();
			bindIndicesBuffer();
			unbindVAO();

			m_mesh->destroy();
			delete m_mesh;
			m_mesh = nullptr;
			return true;
		}

		void MeshComponent::draw() {
			glBindVertexArray(m_vao);

			m_material->use();// pass in 4 matrix
			
			fscene::CameraComponent* camera = fhelpers::Singleton<fcore::CameraManager>::getInstance().getActiveCamera();

			m_material->loadCamera(camera->getViewMatrix(),
				fmath::Matrix4::perspective(50.0f, 800.0f / 500.0f, 0.1f, 1000.0f),  //get that from camera too?
				this->getParent()->getComponent<TransformComponent>()->getWorldMatrix());
			
			glDrawElements(GL_TRIANGLES, m_indicesSize, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			m_material->unuse();
		}

		void MeshComponent::update() {
		}

		bool MeshComponent::shutdown() {
			glDeleteVertexArrays(1, &m_vao);

			for (GLuint& vbo : m_vbos) {
				glDeleteBuffers(1, &vbo);
			}
			
			m_vbos.clear();

			m_material->destroy();
			m_material = nullptr;
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

			glBufferData(GL_ARRAY_BUFFER, m_vecticesSize * sizeof(fmath::Vector3), &(m_mesh->getVertices()[0]), GL_STATIC_DRAW);

			// the meaning of each attribute
			// 1 - attribute position
			// 2 - the size of the array (3 because we only have x,y,z for now
			// 3 - the type of the data being passed in
			// 4 - if the data is normalized
			// 5 - distance between each vertices
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			glGenBuffers(1, &vbo);
			m_vbos.push_back(vbo);
			//start using this vbo
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, m_vecticesSize * sizeof(fmath::Vector3), &(m_mesh->getNormals()[0]), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			glGenBuffers(1, &vbo);
			m_vbos.push_back(vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, m_vecticesSize * sizeof(fmath::Vector2), &(m_mesh->getTextureCoords()[0]), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

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
			
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesSize * sizeof(GL_INT), &(m_mesh->getIndices()[0]), GL_STATIC_DRAW);
		}
	}
}