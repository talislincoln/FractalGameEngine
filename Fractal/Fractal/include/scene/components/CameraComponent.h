#ifndef _CAMERACOMPONENT_H
#define _CAMERACOMPONENT_H

#include <FractalMath\Matrix.h>

#include "scene\Component.h"

#include <gl\glew.h>
namespace fractal {
	namespace fscene {
		class TransformComponent;

		class CameraComponent : public Component
		{
		public:
			CameraComponent(const std::string& name = "");
			virtual ~CameraComponent();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			const fmath::Matrix4 getViewMatrix() const;

			void updateCameraVectors();

			inline fmath::Vector3 getFront() {
				return m_front;
			}
			inline fmath::Vector3 getRight() {
				return m_front.cross(m_up);
			}
			inline fmath::Vector3 getUp() {
				return m_up;
			}
		private:
			TransformComponent* m_transformComponent;
			GLfloat m_zoom;
			fmath::Vector3 m_front, m_up;
		};
	}
}

#endif // !_CAMERACOMPONENT_H
