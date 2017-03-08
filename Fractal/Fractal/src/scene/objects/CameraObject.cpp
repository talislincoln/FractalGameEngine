#include "scene\objects\CameraObject.h"

#include "scene\components\CameraComponent.h"
#include "scene\components\TransformComponent.h"

#include "helpers\Singleton.h"
#include "core\systems\manager\CameraManager.h"

namespace fractal {
	namespace fscene {
		CameraObject::CameraObject(const std::string& name, bool setActive) :
			GameObject(name),
			m_cameraComponent(new CameraComponent()),
			m_transformComponent(new TransformComponent())
		{
			fhelpers::Singleton<fcore::CameraManager>::getInstance().addCamera(this, setActive);
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

		void CameraObject::draw() {
			for (Component* obj : getComponents())
			{
				IDrawable* drawable_obj = dynamic_cast<IDrawable*>(obj);
				if (drawable_obj == nullptr)
					continue;

				if (drawable_obj->getCanDraw())
					drawable_obj->draw();
			}
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

		CameraComponent* CameraObject::getCamera() const {
			return m_cameraComponent;
		}

		TransformComponent* CameraObject::getTransform() const {
			return m_transformComponent;
		}
	}
}