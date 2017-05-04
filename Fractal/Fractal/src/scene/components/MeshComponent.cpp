#include "scene\components\MeshComponent.h"

#include "helpers\Singleton.h"
#include "scene\components\TransformComponent.h"
#include "core\systems\manager\SystemManager.h"
#include <FractalMath\Matrix.h>
#include "scene\GameObject.h"
#include <assert.h>
#include "core\systems\Window.h"
#include <Fractal\include\core\systems\manager\CameraManager.h>
#include <Fractal\include\scene\objects\CameraObject.h>
namespace fractal {
	namespace fscene {
		using namespace fmath;
		MeshComponent::MeshComponent(fgraphics::Material* m, fgraphics::Vao* vao_) :
			Component("MeshComponent"),
			m_material(m), m_vao(vao_)
		{
			//should be empty
		}
		MeshComponent::MeshComponent(fgraphics::MeshData* md_, fgraphics::Material* m) :
			Component("MeshComponent"),
			m_material(m)
		{
			m_vao = new fgraphics::Vao();
			m_vao->loadMeshIntoOpenGL(md_);
			//should be empty
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
				fmath::Matrix4::perspective(30.0f, WWIDTH / WHEIGHT, 0.1f, 1000.0f),  //get that from camera too?
				this->getParent()->getComponent<TransformComponent>()->getWorldMatrix());

			m_material->loadShineVariables(m_material->getShineDamper(), m_material->getReflectivity());

			///TODO NEED TO ACTUALLY IMPORT THE LIGHTING HERE!!!
			//m_material->loadLight(fmath::Vector3(5.0f, 5.0f, 5.0f), fmath::Vector3(1.0f,1.0f,1.0f));
			//;w; test
			m_material->loadProperties(camera->getParent()->getComponent<TransformComponent>()->getPosition());
			m_material->loadMaterial(0.0f, 1.0f, 32.0f);
			m_material->loadDirectional(fmath::Vector3(-0.2f, -1.0f, -0.3f), fmath::Vector3(0.05f, 0.05f, 0.05f), fmath::Vector3(0.4f, 0.4f, 0.4f), fmath::Vector3(0.5f, 0.5f, 0.5f));
			m_material->loadPoint(fmath::Vector3(0.7f, 0.2f, 2.0f), fmath::Vector3(0.05f, 0.05f, 0.05f), fmath::Vector3(0.8f, 0.8f, 0.8f), fmath::Vector3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
			m_material->loadSpot(fmath::Vector3(0.7f, 0.2f, 2.0f), camera->getParent()->getComponent<TransformComponent>()->getPosition().FRONT, fmath::Vector3(0.0f, 0.0f, 0.0f), fmath::Vector3(1.0f, 1.0f, 1.0f), fmath::Vector3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032, cos(toRadians(12.5f)), cos(toRadians(15.0f)));
			//;w; ^ change the second one to front?

			//m_material->loadTest(fmath::Vector3(1.0f, 1.0f, 1.0f), fmath::Vector3(0.5f, 0.5f, 0.5f), fmath::Vector3(1.0f, 1.0f, 1.0f), 1.0f, 0.022f, 0.0019f, 0.0f, 1.0f, 80.0f);
			//m_material->loadTest2(camera->getParent()->getComponent<TransformComponent>()->getPosition(), camera->getParent()->getComponent<TransformComponent>()->getPosition());
			//m_material->loadLight(camera->getPosition(), fmath::Vector3(1.0f,1.0f,1.0f));

			glDrawElements(GL_TRIANGLES, m_vao->indicesSize, GL_UNSIGNED_INT, 0);
			m_vao->unbind();
			m_material->unuse();
		}

		void MeshComponent::update() {
		}

		bool MeshComponent::shutdown() {
			if (m_vao != nullptr) {
				m_vao->destroy();
				delete(m_vao);
				m_vao = nullptr;
			}
			if (m_material != nullptr) {
				m_material->destroy();
				m_material = nullptr;
			}
			return true;
		}

		void MeshComponent::setTexture(fgraphics::Texture * texture)
		{
			m_material->loadNewTexture(texture);
		}
	}
}