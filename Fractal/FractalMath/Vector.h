#ifndef _VECTOR_H
#define _VECTOR_H

#include <iostream>
namespace fractal {
	namespace fmath {
#ifndef VERY_SMALL
#define VERY_SMALL 1.0e-7f
#endif
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
		struct Vector3 {
			float x; ///< x coordinate of the vector
			float y; ///< y coordinate of the vector
			float z; ///< z coordinate of the vector

			/**
			\brief Default and scalar constructor.
			The construct takes a number and set x, y and z to be that number.
			If a number is not provided, zero (0.0) is set as default.
			\param s number to be set for all coordinates of the vector
			*/
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

			inline void load(const float x, const float y, const float z) {
				this->x = x;
				this->y = y;
				this->z = z;
			}

			inline Vector3& add(const Vector3& other) {
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}
			inline Vector3& subtract(const Vector3& other) {
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}
			inline Vector3& multiply(const Vector3& other) {
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}

			inline float dot(const Vector3& other) const {
				return x * other.x + y * other.y + z * other.z;
			}
			inline const Vector3 cross(const Vector3& other) const {
				return Vector3(y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x);
			}
			inline Vector3& normalize() {
				const float magnitude = this->magnitude();
			#ifdef _DEBUG 
				if (magnitude < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

				return *this /= magnitude;
			}
			inline const float magnitude() const {
				return float(sqrt(x * x + y * y + z * z));
			}


			inline Vector3& operator= (const Vector3& other) {
				load(other.x, other.y, other.z);
				return *this;
			}

			inline const Vector3 operator - () const {
				return Vector3(-x, -y, -z);
			}

			inline const Vector3 operator+(const Vector3& other) const {
				return Vector3(x + other.x, y + other.y, z + other.z);
			}

			inline const Vector3 operator-(const Vector3& other) const {
				return Vector3(x - other.x, y - other.y, z - other.z);
			}

			inline const Vector3 operator*(const Vector3& other) const {
				return Vector3(x * other.x, y * other.y, z * other.z);
			}

			inline const Vector3 operator*(const float s) const {
				return Vector3(s*x, s*y, s*z);
			}

			inline friend const Vector3 operator*(const float s, const Vector3& other) {
				return other * s;
			}

			inline const Vector3 operator/(const float s) const {
				#ifdef _DEBUG
				if (fabs(s) < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
				#endif

				float r = 1.0f / s;
				return *this * r;
			}

			inline Vector3& operator+=(const Vector3& other) {
				return add(other);
			}
			inline Vector3& operator-=(const Vector3& other) {
				return subtract(other);
			}
			inline Vector3& operator*=(const Vector3& other) {
				return multiply(other);
			}
			inline Vector3& operator/=(const float s) {

				//only checks if division by zero in debug mode
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

			inline bool operator==(const Vector3& other) const {
				return x == other.x && y == other.y && z == other.z;
			}
			inline bool operator!=(const Vector3& other) const {
				return x != other.x || y != other.y || z != other.z;
			}

			inline const float operator [] (int index) const {
				return *(&x + index);
			}
			inline float& operator [] (int index) {
				return *(&x + index);
			}

			inline operator const float* () const {
				return static_cast<const float*>(&x);
			}
			inline operator float* () {
				return static_cast<float*>(&x);
			}

			inline friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector) {
				stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";

				return stream;
			}

			private:

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

			inline Vector4(const Vector3& other) {
				load(other.x, other.y, other.z, 1.0f);
			}

			inline Vector4(const Vector4& other) {
				load(other.x, other.y, other.z, other.w);
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