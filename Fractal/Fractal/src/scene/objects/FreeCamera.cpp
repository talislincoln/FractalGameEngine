#include "scene\objects\FreeCamera.h"
#include "core\systems\Input.h"
#include "core\systems\manager\SystemManager.h"
#include "helpers\Singleton.h"
#include "scene\components\TransformComponent.h"

#include <FractalMath\Quaternion.h>

namespace fractal {
	namespace fscene {
		FreeCamera::FreeCamera(const std::string& name, float speed) :
			CameraObject("FreeCamera"),
			MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY)//, Camera options
		{

		}

		FreeCamera::~FreeCamera() {

		}

		bool FreeCamera::initialize() {
			return CameraObject::initialize();
		}

		void FreeCamera::update() {
			CameraObject::update();
			this->mouse = this->m_input->getMouseMovement() * MouseSensitivity;
			this->getTransform()->rotate(fmath::Quaternion::fromEuler(mouse.y ,mouse.x , 0.0f ));
		}

		bool FreeCamera::shutdown() {
			return CameraObject::shutdown();
		}

		void FreeCamera::setupInput(fractal::fcore::Input* input) {
			using namespace fcore;
			m_input = input;
			input->bindInput(InputBinding(SDLK_w, std::bind(&FreeCamera::moveUp, this), InputStateType::DOWN));
			input->bindInput(InputBinding(SDLK_s, std::bind(&FreeCamera::moveDown, this), InputStateType::DOWN));
			input->bindInput(InputBinding(SDLK_a, std::bind(&FreeCamera::moveLeft, this), InputStateType::DOWN));
			input->bindInput(InputBinding(SDLK_d, std::bind(&FreeCamera::moveRight, this), InputStateType::DOWN));
		}

		void FreeCamera::setSpeed(float speed) {
			m_speed = speed;
		}

		float FreeCamera::getSpeed() const {
			return m_speed;
		}
		fmath::Matrix4 FreeCamera::getViewMatrix() const {
			return CameraObject::getViewMatrix();
			//return fmath::Matrix4::lookAt(this->getTransform()->getPosition(), this->getTransform()->getPosition() + Front, this->Up);
		}

		void FreeCamera::moveUp() {
			GLfloat velocity = this->MovementSpeed * 0.01f;
			this->getTransform()->translate(this->getFront() * velocity);
		}
		void FreeCamera::moveDown() {
			GLfloat velocity = this->MovementSpeed * 0.01f;
			this->getTransform()->translate(-this->getFront() * velocity);
		}

		void FreeCamera::moveLeft() {
			GLfloat velocity = this->MovementSpeed * 0.01f;
			this->getTransform()->translate(-this->getRight() * velocity);
		}

		void FreeCamera::moveRight() {
			GLfloat velocity = this->MovementSpeed * 0.01f;
			this->getTransform()->translate(this->getRight() * velocity);
		}

		void FreeCamera::lookRight() {
		}

	}
}