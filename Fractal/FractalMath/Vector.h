#ifndef _VECTOR_H
#define _VECTOR_H

#ifndef _POINT_H
#include "Point.h"
#endif // !_POINT_H

namespace fractal {
	namespace fmath {

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
#ifndef DEGREES_TO_RADIANS
#define DEGREES_TO_RADIANS (M_PI / 180.0f)
#endif	
		///Structure that defines a Vector 2 (x, y)
		struct Vector2 {
			float x, y;

			inline Vector2(float x = 0.0f, float y = 0.0f) {
				load(x, y);
			}
			inline void load(const float x, const float y) {
				this->x = x;
				this->y = y;
			}
		};

		///Structure that defines a Vector 3 (x, y, z)
		struct Vector3 : Point3 {

			/**
			\brief Default and scalar constructor.
			The construct takes a number and set x, y and z to be that number.
			If a number is not provided, zero (0.0) is set as default.
			\param s number to be set for all coordinates of the vector
			*/
			inline Vector3(const Point3& p) {
				load(p.x, p.y, p.z);
			}

			inline Vector3(float s = float(0.0)) {
				load(s, s, s);
			}

			inline Vector3(const float x, const float y, const float z) { 
				load(x, y, z); 
			}

			inline Vector3(const Vector3& v) {
				load(v.x, v.y, v.z);
			}

			inline Vector3(const Vector2& xy, float z) {
				load(xy.x, xy.y, z);
			}

			inline float dot(const Vector3& other) const {
				return x * other.x + y * other.y + z * other.z;
			}

			inline const Vector3 cross(const Vector3& other) const {
				return Vector3(y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x);
			}
			inline const Vector3 inverse() const{
				return Vector3(1.0f / x, 1.0f/y, 1.0f/z);
			}

			inline Vector3& normalize() {
				const float magnitude = this->magnitude();
			#ifdef _DEBUG 
				if (magnitude < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif
				*this /= magnitude;
				return *this;
			}

			inline const Vector3 getNormilizedVector() const {
				const float magnitude = this->magnitude();
				#ifdef _DEBUG 
				if (magnitude < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
				#endif
				return Vector3(*this / magnitude);
			}

			inline const float magnitude() const {
				return float(sqrt(x * x + y * y + z * z));
			}

			inline const float operator [] (int index) const {
				return *(&x + index);
			}

			inline float& operator [] (int index) {
				return *(&x + index);
			}
		};

		///Structure that defines a Vector 4, inherits from Vector 3
		struct Vector4 : public Vector3 {
			// x = x
			// y = y
			// z = z from vec3
			float w; ///< 4th coordinate of the vector

			inline Vector4(const float s = float(0.0f)) {
				load(s, s, s, s);
			}

			inline Vector4(const float x, const float y, const float z, const float w) {
				load(x, y, z, w);
			}

			inline Vector4(const Vector4& other) {
				load(other.x, other.y, other.z, other.w);
			}
			inline Vector4(const Vector3& other) {
				load(other.x, other.y, other.z, 1.0f);
			}
			inline Vector4(const Point3& other) {
				load(other.x, other.y, other.z, 1.0f);
			}

			inline void load(const float x, const float y, const float z, const float w) {
				Vector3::load(x, y, z);
				this->w = w;
			}

			inline Vector4& add(const Vector4& other) {
				Vector3::add(other);
				w += other.w;
				return *this;
			}

			inline Vector4& subtract(const Vector4& other) {
				Vector3::subtract(other);
				w -= other.w;
				return *this;
			}

			inline Vector4& multiply(const Vector4& other) {
				Vector3::multiply(other);
				w *= other.w;
				return *this;
			}

			inline float dot(const Vector3& other) const {
				return x * other.x + y * other.y + z * other.z + w * 1;
			}
			inline float dot(const Vector4& other) const {
				return x * other.x + y * other.y + z * other.z + w * other.w;
			}

			inline Vector4& normalize() {
				const float magnitude = this->magnitude();
			
				//only checks if division by zero in debug mode
				#ifdef _DEBUG 
				if (magnitude < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
				#endif

				return *this /= magnitude;
			}

			inline const float magnitude() const {
				return float(sqrt(x * x + y * y + z * z + w * w));
			}

			inline Vector4& operator= (const Vector4& other) {
				load(other.x, other.y, other.z, other.w);
				return *this;
			}

			inline const Vector4 operator - () const {
				return Vector4(-x, -y, -z, -w);
			}

			inline const Vector4 operator+(const Vector4& other) const {
				return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
			}

			inline const Vector4 operator-(const Vector4& other) const {
				return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
			}

			inline const Vector4 operator*(const Vector4& other) const {
				return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
			}

			inline const Vector4 operator*(const float s) const {
				return Vector4(x * s, y * s, z * s, w * s);
			}

			inline friend const Vector4 operator*(const float s, const Vector4& other) {
				return other * s;
			}

			inline const Vector4 operator/(const float s) const {
				#ifdef _DEBUG
				if (fabs(s) < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
				#endif

				float r = 1.0f / s;
				return *this * r;
			}

			inline Vector4& operator += (const Vector4& other) {
				return add(other);
			}

			inline Vector4& operator -= (const Vector4& other) {
				return subtract(other);
			}

			inline Vector4& operator *= (const Vector4& other) {
				return multiply(other);
			}

			inline Vector4& operator /= (const float s) {
				#ifdef _DEBUG 
				if (std::fabs(s) < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
				#endif

				float r = 1.0f / s;
				*this *= r;
				return *this;
			}

			inline bool operator==(const Vector4& other) const {
				return x == other.x && y == other.y && z == other.z && w == other.w;
			}

			inline bool operator!=(const Vector4& other) const {
				return x != other.x || y != other.y || z != other.z || w != other.w;
			}

			inline operator const float* () const {
				return static_cast<const float*>(&x);
			}

			inline operator float* () {
				return static_cast<float*>(&x);
			}

			inline friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector) {
				stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";

				return stream;
			}
		};
	}
}

#endif // !_VECTOR_H