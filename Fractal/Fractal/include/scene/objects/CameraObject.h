#ifndef _CAMERAOBJECT_H
#define _CAMERAOBJECT_H
#include <Fractal\include\scene\GameObject.h>
#include <Fractal\include\interfaces\IDrawable.h>
#include "scene\components\CameraComponent.h"
namespace fractal {
	namespace fscene {

		//Forward declarations
		class TransformComponent;

		class CameraObject : public GameObject{
		public:
			CameraObject(const std::string& name = "CameraObject", bool setActive = true);
			virtual ~CameraObject();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			virtual fmath::Matrix4 getViewMatrix() const;

			inline fmath::Vector3 getFront() {
				return m_cameraComponent->getFront();
			}
			inline fmath::Vector3 getRight() {
				return m_cameraComponent->getRight();
			}
			inline fmath::Vector3 getUp() {
				return m_cameraComponent->getUp();
			}
			CameraComponent* getCamera() const;
			TransformComponent* getTransform() const;

		private:
			CameraComponent* m_cameraComponent;
			TransformComponent* m_transformComponent;
		};
	}
}

#endif // !_CAMERAOBJECT_H
