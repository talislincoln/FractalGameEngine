#ifndef _QUATERNION_H
#define _QUATERNION_H

#ifndef _MATRIX_H
#include "matrix.h"
#endif // !_POINT_H

namespace fractal {
	namespace fmath {
		struct Quaternion : Vector3
		{
			float w;

			inline void load(float _w, float _x, float _y, float _z) {
				w = _w; x = _x; y = _y; z = _z;
			}

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

			/// An assignment operator   
			inline Quaternion& operator = (const Quaternion& q) {
				load(q.w, q.x, q.y, q.z);
				return *this;
			}

			/// Take the negative of a Quaternion
			inline const Quaternion operator - () const {
				return Quaternion(-w, -x, -y, -z);
			}

			/// Multiply a two quaternions - using the right-hand rule  
			inline const Quaternion operator * (const Quaternion& q) const {
				Vector3 ijk(w*q + q.w * (*this) + this->cross(q));
				return Quaternion(w * q.w - this->dot(q), ijk.x, ijk.y, ijk.z);
			}
			inline const Quaternion operator / (const float f) const {
				return Quaternion(w / f, x / f, y / f, z / f);
			}
			/*inline const Quaternion& scaleQuaternion (const Vector3& scale) const {
				Quaternion t(w, x, y, z);
				t.x *= scale.x;
				t.y *= scale.y;
				t.z *= scale.z;
				return *this;
			}*/
			/// Multiply a quaternion by a Vector3 - using the right-hand rule 
			inline const Quaternion operator * (const Vector4& v) const {
				Vector3 ijk(w*v + v.w * (*this) + this->cross(v));
				return Quaternion(w * v.w - this->dot(v), ijk.x, ijk.y, ijk.z);
			}

			inline const Quaternion conjugate() const {
				return Quaternion(w, -x, -y, -z);
			}

			inline const Quaternion inverse() const {

				return Quaternion(w, -x, -y, -z) / (w * w) + (x * x) + (y * y) + (z * z);
			}

			inline Vector3 rotate(const Vector3& v) const {
				/// This is the standard way q*v*q^-1
				///return Vector3( (*this) * v * (*this).conjugate());

				/// I read an article that shows this way to be faster and it works! 
				Vector3 v2 = this->cross(v);
				return v + v2 * (2.0f * w) + this->cross(v2) * 2.0f;
			}

			inline const float quaternionDot(Quaternion& q_) const{ 
				return (w * q_.w + x * q_.x + y * q_.y + z * q_.z);
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


			/// To work this out you can multipy the three angles as quaternions together. 
			/// q = q(yaw) * q(pitch) * q(yaw) the result is as follows
			inline const Quaternion fromEuler(float _yaw, float _pitch, float _roll) {
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
			}

			inline float mag() {
				return(sqrt((w * w) + (x * x) + (y * y) + (z * z)));
			}

			inline void print() {
				printf("%f %f %f %f\n", w, x, y, z);
			}
		};
	}
}


#endif