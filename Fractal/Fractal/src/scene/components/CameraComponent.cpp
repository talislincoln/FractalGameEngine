#include "scene\components\CameraComponent.h"

#include "scene\GameObject.h"
#include "scene\components\TransformComponent.h"
#include "helpers\Singleton.h"
#include "core\systems\manager\CameraManager.h"

namespace fractal {
	namespace fscene {
		CameraComponent::CameraComponent(const std::string& name) :
			Component(name == "" ? "CameraComponent" : name), 
			m_transformComponent(nullptr)
		{
			fhelpers::Singleton<fcore::CameraManager>::getInstance().addCamera(this, true);
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

			// Calculate the new Front vector 
			this->m_front = m_transformComponent->getRotation().rotate(fmath::Vector3::FRONT);
			//this->m_front.normalize();
			//  unit vector rotate with unit Q should be a unit vector.  no need to normalize;

			// Also re-calculate the Right and Up vector
			//do we need right?
			this->m_right = m_front.cross(fmath::Vector3::UP).getNormilizedVector();
			this->m_up = m_right.cross(this->m_front).getNormilizedVector();  
			// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			
			//empty
		}
		bool CameraComponent::shutdown() {
			return true;
		}

		const fmath::Matrix4 CameraComponent::getViewMatrix() const {

			return fmath::Matrix4::lookAt(this->m_transformComponent->getPosition(),
				this->m_transformComponent->getPosition() + m_front, m_up);
			//fmath::Matrix4 m = this->m_transformComponent->getWorldMatrix();
			//return fmath::Matrix4::inverse(m);
		}
		void CameraComponent::updateCameraVectors()
		{
		}
	}
}