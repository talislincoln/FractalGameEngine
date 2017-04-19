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
			m_material(m)
		{
			//should be empty
			m_vao = new fgraphics::Vao();
			m_vao->loadMeshIntoOpenGL(mesh);
		}

		MeshComponent::~MeshComponent() {
			//empty
		}

		bool MeshComponent::initialize() {
			return true;
		}

		void MeshComponent::draw() {
			m_vao->bind();
			m_material->use();// pass in 4 matrix
			
			fscene::CameraComponent* camera = fhelpers::Singleton<fcore::CameraManager>::getInstance().getActiveCamera();

			m_material->loadCamera(camera->getViewMatrix(),
				fmath::Matrix4::perspective(30.0f, 800.0f / 500.0f, 0.1f, 1000.0f),  //get that from camera too?
				this->getParent()->getComponent<TransformComponent>()->getWorldMatrix());

			m_material->loadShineVariables(m_material->getShineDamper(), m_material->getReflectivity());

			///TODO NEED TO ACTUALLY IMPORT THE LIGHTING HERE!!!
			//m_material->loadLight(fmath::Vector3(5.0f, 5.0f, 5.0f), fmath::Vector3(1.0f,1.0f,1.0f));
			//;w; test
			m_material->loadTest(fmath::Vector3(0.2f, 0.2f, 0.2f), fmath::Vector3(0.5f, 0.5f, 0.5f), fmath::Vector3(1.0f, 1.0f, 1.0f), 0.01f, 0.09f, 0.032f, 0.0f, 1.0f, 32.0f);
			m_material->loadTest2(camera->getParent()->getComponent<TransformComponent>()->getPosition(), camera->getParent()->getComponent<TransformComponent>()->getPosition());
			m_material->loadLight(camera->getPosition(), fmath::Vector3(1.0f,1.0f,1.0f));
			
			glDrawElements(GL_TRIANGLES, m_vao->indicesSize, GL_UNSIGNED_INT, 0);
			m_vao->unbind();
			m_material->unuse();
		}

		void MeshComponent::update() {
		}

		bool MeshComponent::shutdown() {
			m_vao->destroy();
			delete(m_vao);
			m_vao = nullptr;
			m_material->destroy();
			m_material = nullptr;
			return true;
		}

		void MeshComponent::setTexture(fgraphics::Texture * texture)
		{
			m_material->loadNewTexture(texture);
		}
	}
}