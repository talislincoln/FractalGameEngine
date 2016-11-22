#ifndef _CAMERAOBJECT_H
#define _CAMERAOBJECT_H

#include "scene\GameObject.h"

namespace fractal {
	namespace fscene {

		//Forward declarations
		class CameraComponent;
		class TransformComponent;

		class Camera : public GameObject {
		public:
			Camera(const std::string& name = "", bool setActive = true);
			virtual ~Camera();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			CameraComponent* getCamera() const;
			TransformComponent* getTransform() const;

		private:
			CameraComponent* camera;
			TransformComponent* transform;
		};
	}
}

#endif // !_CAMERAOBJECT_H
