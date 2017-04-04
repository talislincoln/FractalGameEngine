#ifndef _FREECAMERA_H
#define _FREECAMERA_H

#include "CameraObject.h"
#include <Fractal\include\core\systems\Input.h>
#include <FractalMath\Matrix.h>
#include <gl\glew.h>

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
		const GLfloat SPEED = 3.0f;
		const GLfloat SENSITIVTY = 0.25f;

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
			fmath::Matrix4 getViewMatrix() const;

		private:
			void lookRight();
			float m_speed;

		public:
			// Camera options
			GLfloat MovementSpeed;
			GLfloat MouseSensitivity;
			fmath::Vector2 mouse;
			fractal::fcore::Input* m_input;
		};
	}
}

#endif // !_FREECAMERA_H
