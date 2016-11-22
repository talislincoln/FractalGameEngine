#include "scene\CameraObject.h"


namespace fractal {
	namespace fscene {
		Camera::Camera(const std::string& name, bool setActive) {

		}

		Camera::~Camera() {

		}

		bool Camera::initialize() {
			return true;
		}

		void Camera::update() {

		}

		bool Camera::shutdown() {
			return true;
		}

		/*CameraComponent* getCamera() const {
			return new CameraComponent();
		}

		TransformComponent* getTransform() const {
			return nullptr;
		}*/
	}
}