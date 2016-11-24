#ifndef _PHYSICS_MATH
#define _PHYSICS_MATH

#include <FractalMath\Quaternion.h>

namespace fractal {
	namespace fphysics {
		inline float calAngularAcceleration(float torque, float inertia) {
			return torque / inertia;
		}
		inline fmath::Vector3 RolateVector(fmath::Matrix3 angle, fmath::Vector3 xyz) {
			return (angle)* xyz;
		}
		inline fmath::Vector3 calLinearAcceleration(float mass, fmath::Vector3 force) {
			return force / mass;
		}
		inline float calAngularVelocity(float avin, float aa, float dTime) {
			return avin + (aa * dTime);
		}
		inline float calOrientationAngle(float Anglein, float avin, float dTime, float aa) {
			return Anglein + (avin * dTime) + (0.5f * aa * dTime * dTime);
		}
		inline fmath::Vector3 calFinalVelocity(fmath::Vector3 vXYin, fmath::Vector3 aXYin, float dTime) {
			return vXYin + (aXYin * dTime);
		}
		inline fmath::Vector3 calLinearPos(fmath::Vector3 posXYin, fmath::Vector3 vXYin, fmath::Vector3 a, float dTime) {
			return posXYin + (vXYin * dTime) + (a * (dTime * dTime * 0.5f));
		}
	}
}



#endif // !_PHYSICS_MATH
