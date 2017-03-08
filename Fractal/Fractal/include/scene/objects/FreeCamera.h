#ifndef _FREECAMERA_H
#define _FREECAMERA_H

#include "CameraObject.h"
#include <Fractal\include\core\systems\Input.h>

#include <gl\glew.h>
#include <FractalMath\Math.h>
#include <FractalMath\Matrix.h>

namespace fractal {
	namespace fscene {

		// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
		enum Camera_Movement {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};

		// Default camera values
		const GLfloat YAW = -90.0f;
		const GLfloat PITCH = 0.0f;
		const GLfloat SPEED = 3.0f;
		const GLfloat SENSITIVTY = 0.25f;
		const GLfloat ZOOM = 45.0f;

		class FreeCamera : public CameraObject {
		public:
			FreeCamera(const std::string& name = "", float speed = 0.1f);
			virtual ~FreeCamera();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			virtual void setupInput(fractal::fcore::Input* input);

			void setSpeed(float speed);
			float getSpeed() const;

			void moveUp();
			void moveDown();
			void moveLeft();
			void moveRight();

			//new functions
			void updateCameraVectors();
			fmath::Matrix4 getViewMatrix();

		private:
			float m_speed;

		public:
			GLfloat Yaw;
			GLfloat Pitch;
			// Camera options
			GLfloat MovementSpeed;
			GLfloat MouseSensitivity;
			GLfloat Zoom;

			// Camera Attributes
			fmath::Vector3 Front;
			fmath::Vector3 Up;
			fmath::Vector3 Right;
			fmath::Vector3 WorldUp;
		};
	}
}

#endif // !_FREECAMERA_H
