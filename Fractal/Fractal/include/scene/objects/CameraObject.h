#ifndef _CAMERAOBJECT_H
#define _CAMERAOBJECT_H

#include "scene\GameObject.h"
#include "interfaces\IDrawable.h"

namespace fractal {
	namespace fscene {

		//Forward declarations
		class CameraComponent;
		class TransformComponent;

		class CameraObject : public GameObject, public IDrawable {
		public:
			CameraObject(const std::string& name = "CameraObject", bool setActive = true);
			virtual ~CameraObject();

			virtual bool initialize();
			virtual void update();
			virtual void draw();
			virtual bool shutdown();

			CameraComponent* getCamera() const;
			TransformComponent* getTransform() const;

		private:
			CameraComponent* m_cameraComponent;
			TransformComponent* m_transformComponent;
		};
	}
}

#endif // !_CAMERAOBJECT_H
