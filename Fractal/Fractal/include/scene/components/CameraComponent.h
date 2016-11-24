#ifndef _CAMERACOMPONENT_H
#define _CAMERACOMPONENT_H

#include <FractalMath\Matrix.h>

#include "scene\Component.h"

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

		private:
			TransformComponent* m_transformComponent;
		};
	}
}

#endif // !_CAMERACOMPONENT_H
