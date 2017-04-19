#ifndef _QUATERNION_H
#define _QUATERNION_H

#ifndef _MATRIX_H
#include "matrix.h"
#endif 

#include <algorithm>

namespace fractal {
	namespace fmath {
		struct Quaternion : Vector3
		{
			float w;

			/// This is the unit quaterion by definition 
			inline Quaternion() {
				load(1.0f, 0.0f, 0.0f, 0.0f);
			}

			inline Quaternion(float _w, float _x, float _y, float _z) {
				load(_w, _x, _y, _z);
			}

			/// This is the constructor for a rotation  quartinion 
			/// The w component is degrees and n is the axis of rotations 
			inline Quaternion(float angle, const Vector3& n) {
				Vector3 v = n.getNormilizedVector();
				angle *= DEGREES_TO_RADIANS; ///
				load(cos(angle / 2.0f), sin(angle / 2.0f)*n.x, sin(angle / 2.0f)*n.y, sin(angle / 2.0f)*n.z);
			}

			inline Quaternion(const Vector4& n) {
				//angle *= DEGREES_TO_RADIANS; ///
				load(cos(n.w / 2.0f), sin(n.w / 2.0f)*n.x, sin(n.w / 2.0f)*n.y, sin(n.w / 2.0f)*n.z);
			}

			/// A copy constructor
			inline Quaternion(const Quaternion& q) {
				load(q.w, q.x, q.y, q.z);
			}

			inline static const Quaternion lerp(const Quaternion& q1, const Quaternion& q2, float t) {
				Quaternion q = (1-t)*q1 + (q2*t);

				return q.getNormilizedVector();
			}

			inline static const Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t) {
				float dp = q1.dot(q2);
				//std::clamp(dp, -1.0f, 1.0f);

				return NULL;
			}

			inline void load(float _w, float _x, float _y, float _z) {
				w = _w; x = _x; y = _y; z = _z;
			}

			inline const Quaternion getNormalizedQuarternion() const {
				float mag = this->mag();

				return Quaternion (w / mag, x / mag, y / mag, z / mag);
			}

			/// An assignment operator   
			inline Quaternion& operator = (const Quaternion& q) {
				load(q.w, q.x, q.y, q.z);
				return *this;
			}
			inline Quaternion& operator /= (const float f) {
				*this = *this / f;
				return *this;
			}
			inline Quaternion& operator *= (const Quaternion& q) {
				*this = *this * q;
				return *this;
			}
			/// Take the negative of a Quaternion
			inline const Quaternion operator - () const {
				return Quaternion(-w, -x, -y, -z);
			}

			inline const Quaternion operator+(const Quaternion& other) const {
				return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
			}

			inline const Quaternion operator-(const Quaternion& other) const {
				return Quaternion(w - other.w,x - other.x, y - other.y, z - other.z);
			}

			/// Multiply a two quaternions - using the right-hand rule  
			inline const Quaternion operator * (const Quaternion& q) const {
				Vector3 ijk((w * (Vector3)q) + q.w * (Vector3)(*this) + this->cross(q));
				return Quaternion(w * q.w - this->dot(q), ijk.x, ijk.y, ijk.z);
			}

			inline const Quaternion operator / (const float f) const {
				return Quaternion(w / f, x / f, y / f, z / f);
			}

			inline const Quaternion operator*(const float s) const {
				return Quaternion(w * s,x * s, y * s, z * s);
			}

			inline friend const Quaternion operator*(const float s, const Quaternion& other)  {
				return other * s;
			}

			/// Multiply a quaternion by a Vector3 - using the right-hand rule 
			inline const Quaternion operator * (const Vector4& v) const {
				Vector3 ijk(w*v + v.w * (*this) + this->cross(v));
				return Quaternion(w * v.w - this->dot(v), ijk.x, ijk.y, ijk.z);
			}

			inline const Quaternion conjugate() const {
				return Quaternion(w, -x, -y, -z);
			}

			inline const Quaternion inverse() const {
				return Quaternion(w, -x, -y, -z) / ((w * w) + (x * x) + (y * y) + (z * z));
			}

			inline Vector3 rotate(const Vector3& v) const {
				/// This is the standard way q*v*q^-1
				///return Vector3( (*this) * v * (*this).conjugate());

				/// I read an article that shows this way to be faster and it works! 
				Vector3 v2 = this->cross(v);
				return v + v2 * (2.0f * w) + this->cross(v2) * 2.0f;
			}

			inline const float quaternionDot(const Quaternion& q_) const{ 
				return (w * q_.w + x * q_.x + y * q_.y + z * q_.z);
			}

			inline const float getAngleBetween(const Quaternion& q) const {
				if (this->quaternionDot(q) < 0)
				{
					return acos(-this->quaternionDot(q)) * 2 * 180 / 3.14f;
				}
				return acos(this->quaternionDot(q)) *2 * 180 / 3.14f;
			}

			inline const Matrix3 toMatrix3() const {
				return Matrix3((1.0f - 2.0f*y*y - 2.0f*z*z), (2.0f*x*y + 2.0f * z*w), (2.0f*x*z - 2.0f*y*w),
					(2.0f*x*y - 2.0f*z*w), (1.0f - 2.0f*x*x - 2.0f*z*z), (2 * y*z + 2 * x*w),
					(2.0f*x*z + 2.0f*y*w), (2.0f*y*z - 2 * x*w), (1.0f - 2.0f*x*x - 2.0f*y*y));
			}

			inline const Matrix4 toMatrix() const {
				/// This is the fastest way I know...
				return Matrix4((1.0f - 2.0f*y*y - 2.0f*z*z), (2.0f*x*y + 2.0f * z*w), (2.0f*x*z - 2.0f*y*w), 0.0f,
					(2.0f*x*y - 2.0f*z*w), (1.0f - 2.0f*x*x - 2.0f*z*z), (2 * y*z + 2 * x*w), 0.0f,
					(2.0f*x*z + 2.0f*y*w), (2.0f*y*z - 2 * x*w), (1.0f - 2.0f*x*x - 2.0f*y*y), 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);

				/// ... but this is the coolest . My way is just a bit faster on single processor machines,
				/// this method is faster on parallel multicore machines.
				/*** Matrix m1( w,   z,  -y,  x,
				-z,   w,   x,  y,
				y,  -x,   w,  z,
				- x,  -y,  -z,  w);

				Matrix m2(  w,   z,  -y,  -x,
				-z,   w,   x,  -y,
				y,  -x,   w,  -z,
				-x,   y,   z,   w);
				return m1 * m2; ***/
			}
			inline const float angleBetween(Quaternion& other) const {
				return acosf(abs(this->quaternionDot(other))) *2.0f *57.2957795f;// * 57.2957795f; // To degrees!;
			}

			/*inline static const Quaternion fromEuler(float _yaw, float _pitch, float _roll) {


				float cosYaw = cos(0.5f *_yaw * DEGREES_TO_RADIANS);
				float cosPitch = cos(0.5f * _pitch * DEGREES_TO_RADIANS);
				float cosRoll = cos(0.5f  *_roll * DEGREES_TO_RADIANS);
				float sinYaw = sin(0.5f *_yaw * DEGREES_TO_RADIANS);
				float sinPitch = sin(0.5f * _pitch * DEGREES_TO_RADIANS);
				float sinRoll = sin(0.5f  *_roll * DEGREES_TO_RADIANS);
				return Quaternion(
					(cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll),
					(cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
					(cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
					(sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll));
			}*/
			
			inline static const Quaternion fromEuler(float _yaw, float _pitch, float _roll) {

				float angle;

				angle = _yaw * 0.5f * DEGREES_TO_RADIANS;
				const float sr = sinf(angle);
				const float cr = cosf(angle);

				angle = _pitch * 0.5f * DEGREES_TO_RADIANS;
				const float sp = sinf(angle);
				const float cp = cosf(angle);

				angle = _roll * 0.5f * DEGREES_TO_RADIANS;
				const float sy = sinf(angle);
				const float cy = cosf(angle);

				const float cpcy = cp * cy;
				const float spcy = sp * cy;
				const float cpsy = cp * sy;
				const float spsy = sp * sy;

				Quaternion q;


				q.w = (cr * cpcy + sr * spsy);
				q.x = (sr * cpcy - cr * spsy);
				q.y = (cr * spcy + sr * cpsy);
				q.z = (cr * cpsy - sr * spcy);

				return q.normalize();
			}
			

			inline Quaternion& normalize() {
				return *this /= mag();
			}

			inline Quaternion getNormilized() const {
				float n = (w * w) + (x * x) + (y * y) + (z * z);
				return (*this / mag());
			}

			inline float mag() const {
					float n = (w * w) + (x * x) + (y * y) + (z * z);
					if (n == 1) {
						return n;
					}
					return(sqrt(n));
			}

			inline void integrate(const Vector3& dv, float dt)
			{
				Quaternion q(float(0.0), dv.x * dt, dv.y * dt, dv.z * dt);

				q *= *this;

				x += q.x * float(0.5);
				y += q.y * float(0.5);
				z += q.z * float(0.5);
				w += q.w * float(0.5);

				*this = this->getNormilized();
			}

			inline void print() {
				printf("%f %f %f %f\n", w, x, y, z);
			}
		};
	}
}

#endif