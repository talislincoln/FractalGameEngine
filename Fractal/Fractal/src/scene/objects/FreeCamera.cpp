#include "scene\objects\FreeCamera.h"
#include "core\systems\Input.h"
#include "core\systems\manager\SystemManager.h"
#include "helpers\Singleton.h"
#include "scene\components\TransformComponent.h"

#include <SDL\SDL.h>

namespace fractal {
	namespace fscene {
		FreeCamera::FreeCamera(const std::string& name, float speed) :
			CameraObject("FreeCamera"),
			WorldUp(fmath::Vector3(0.0f,1.0f,0.0f)),
			Front(fmath::Vector3(0.0f, 0.0f, -1.0f)),
			Yaw(YAW), Pitch(PITCH), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)//, Camera options
		{
			updateCameraVectors();

		}

		FreeCamera::~FreeCamera() {

		}

		bool FreeCamera::initialize() {
			return CameraObject::initialize();
		}

		void FreeCamera::update() {
			CameraObject::update();
		}

		bool FreeCamera::shutdown() {
			return CameraObject::shutdown();
		}

		void FreeCamera::setupInput(fractal::fcore::Input* input) {
			using namespace fcore;

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

		void FreeCamera::updateCameraVectors()
		{
			// Calculate the new Front vector
			fractal::fmath::Vector3 front;
			front.x = cos(fmath::toRadians(Yaw)) * cos(fmath::toRadians(Pitch));
			front.y = sin(fmath::toRadians(Pitch));
			front.z = sin(fmath::toRadians(Yaw)) * cos(fmath::toRadians(Pitch));
			this->Front = front.normalize();
			// Also re-calculate the Right and Up vector
			this->Right = Front.cross(this->WorldUp).getNormilizedVector();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			this->Up = Right.cross(this->Front).getNormilizedVector();
		}

		fmath::Matrix4 FreeCamera::getViewMatrix() {
			return fmath::Matrix4::lookAt(this->getTransform()->getPosition(), this->getTransform()->getPosition() + Front, this->Up);
		}

		void FreeCamera::moveUp() {
			GLfloat velocity = this->MovementSpeed * 0.01f;
			this->getTransform()->setPosition(this->getTransform()->getPosition() + this->Front * velocity);
		}
		void FreeCamera::moveDown() {
			GLfloat velocity = this->MovementSpeed * 0.01f;
			this->getTransform()->setPosition(this->getTransform()->getPosition() - this->Front * velocity);
		}

		void FreeCamera::moveLeft() {
			GLfloat velocity = this->MovementSpeed * 0.01f;
			this->getTransform()->setPosition(this->getTransform()->getPosition() - this->Right * velocity);
		}

		void FreeCamera::moveRight() {
			GLfloat velocity = this->MovementSpeed * 0.01f;
			this->getTransform()->setPosition(this->getTransform()->getPosition() + this->Right * velocity);
		}
	}
}