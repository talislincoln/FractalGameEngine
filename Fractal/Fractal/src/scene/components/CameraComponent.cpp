#include "scene\components\CameraComponent.h"

#include "scene\GameObject.h"
#include "scene\components\TransformComponent.h"

namespace fractal {
	namespace fscene {
		CameraComponent::CameraComponent(const std::string& name) :
			Component(name == "" ? "CameraComponent" : name),
			m_transformComponent(nullptr)
		{

		}

		CameraComponent::~CameraComponent() {
			//empty
			//no need to delete the world matrix since its a reference to the parent's matrix
			//the parent (gameobject) will take care of it.
		}

		bool CameraComponent::initialize() {
			this->m_transformComponent = getParent()->getComponent<TransformComponent>();

			//Transform on a camera cannot be null
			if (m_transformComponent == nullptr) {
				std::printf("transform in camera is null where it CAN'T BE!");
			}

			return true;
		}

		void CameraComponent::update() {
			//empty
		}



		bool CameraComponent::shutdown() {
			return true;
		}

		const fmath::Matrix4 CameraComponent::getViewMatrix() const {
			fmath::Matrix4 m = this->m_transformComponent->getWorldMatrix();
			return fmath::Matrix4::inverse(m);
		}
	}
}