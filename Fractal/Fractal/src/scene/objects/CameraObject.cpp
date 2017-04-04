#include "scene\objects\CameraObject.h"

#include "scene\components\CameraComponent.h"
#include "scene\components\TransformComponent.h"


namespace fractal {
	namespace fscene {
		CameraObject::CameraObject(const std::string& name, bool setActive) :
			GameObject(name),
			m_cameraComponent(new CameraComponent()),
			m_transformComponent(new TransformComponent())
		{
		}

		CameraObject::~CameraObject() {
		}

		bool CameraObject::initialize() {
			addComponent(this->m_transformComponent);
			addComponent(this->m_cameraComponent);

			return GameObject::initialize();
		}

		void CameraObject::update() {
			GameObject::update();
		}


		bool CameraObject::shutdown() {
			if (!m_cameraComponent->shutdown()) {
				//error
			}

			if (!m_transformComponent->shutdown()) {
				//error
			}
			
			return GameObject::shutdown();
		}

		fmath::Matrix4 CameraObject::getViewMatrix() const
		{
			return m_cameraComponent->getViewMatrix();
		}

		CameraComponent* CameraObject::getCamera() const {
			return m_cameraComponent;
		}

		TransformComponent* CameraObject::getTransform() const {
			return m_transformComponent;
		}
	}
}