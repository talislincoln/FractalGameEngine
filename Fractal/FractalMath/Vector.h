#ifndef _VECTOR_H
#define _VECTOR_H

#include <iostream>
namespace fractal {
	namespace fmath {
#ifndef VERY_SMALL
#define VERY_SMALL 1.0e-7f
#endif
		struct vec2 {
			float x, y;

			vec2(float x, float y) {
				load(x, y);
			}
			inline void load(const float x, const float y) {
				this->x = x;
				this->y = y;
			}
			inline vec2& operator= (const vec3& other) {
				load(other.x, other.y);
				return *this;
			}
		};

		struct vec3 {
			float x, y, z;
			//consturcter
			inline vec3(float s = float(0.0)) {
				load(s, s, s);
			}
			inline vec3(const float x, const float y, const float z) { 
				load(x, y, z); 
			}
			inline vec3(const vec3& v) {
				load(v.x, v.y, v.z);
			}
			inline vec3(const vec2& xy, float z) {
				load(xy.x, xy.y, z);
			}

			inline void load(const float x, const float y, const float z) {
				this->x = x;
				this->y = y;
				this->z = z;
			}

			inline vec3& add(const vec3& other) {
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}
			inline vec3& subtract(const vec3& other) {
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}
			inline vec3& multiply(const vec3& other) {
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}

			inline float dot(const vec3& other) {
				return x * other.x + y * other.y + z * other.z;
			}
			inline const vec3 cross(const vec3& other) {
				return vec3(y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x);
			}
			inline vec3& normalize() {
				const float magnitude = this->magnitude();
			#ifdef _DEBUG 
				if (magnitude < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

				return *this /= magnitude;
			}
			inline const float magnitude() {
				return float(sqrt(x * x + y * y + z * z));
			}


			inline vec3& operator= (const vec3& other) {
				load(other.x, other.y, other.z);
				return *this;
			}
			inline const vec3 operator - () const {
				return vec3(-x, -y, -z);
			}
			inline const vec3 operator+(const vec3& other) const {
				return vec3(x + other.x, y + other.y, z + other.z);
			}
			inline const vec3 operator-(const vec3& other) const {
				return vec3(x - other.x, y - other.y, z - other.z);
			}
			inline const vec3 operator*(const vec3& other) const {
				return vec3(x * other.x, y * other.y, z * other.z);
			}
			inline const vec3 operator*(const float s) const {
				return vec3(s*x, s*y, s*z);
			}
			inline friend const vec3 operator*(const float s, const vec3& other) {
				return other * s;
			}
			inline const vec3 operator/(const float s) const {
			#ifdef _DEBUG
				if (fabs(s) < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

				float r = 1.0f / s;
				return *this * r;
			}

			inline vec3& operator+=(const vec3& other) {
				return add(other);
			}
			inline vec3& operator-=(const vec3& other) {
				return subtract(other);
			}
			inline vec3& operator*=(const vec3& other) {
				return multiply(other);
			}
			inline vec3& operator/=(const float s) {
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

			inline bool operator==(const vec3& other) const {
				return x == other.x && y == other.y && z == other.z;
			}
			inline bool operator!=(const vec3& other) const {
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

			inline friend std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
				stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";

				return stream;
			}
		};

		struct vec4 : public vec3 {
			// x = x
			// y = y
			// z = z from vec3
			float w;

			inline vec4(const float s = float(0.0f)) {
				load(s, s, s, s);
			}
			inline vec4(const float x, const float y, const float z, const float w) {
				load(x, y, z, w);
			}
			inline vec4(const vec3& other) {
				load(other.x, other.y, other.z, 1.0f);
			}
			inline vec4(const vec4& other) {
				load(other.x, other.y, other.z, other.w);
			}

			inline void load(const float x, const float y, const float z, const float w) {
				vec3::load(x, y, z);
				this->w = w;
			}


			inline vec4& add(const vec4& other) {
				vec3::add(other);
				w += other.w;
				return *this;
			}
			inline vec4& subtract(const vec4& other) {
				vec3::subtract(other);
				w -= other.w;
				return *this;
			}
			inline vec4& multiply(const vec4& other) {
				vec3::multiply(other);
				w *= other.w;
				return *this;
			}

			inline float dot(const vec3& other) {
				return x * other.x + y * other.y + z * other.z + w * 1;
			}
			inline float dot(const vec4& other) {
				return x * other.x + y * other.y + z * other.z + w * other.w;
			}

			inline vec4& normalize() {
				const float magnitude = this->magnitude();
			#ifdef _DEBUG 
				if (magnitude < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

				return *this /= magnitude;
			}
			inline const float magnitude() {
				return float(sqrt(x * x + y * y + z * z + w * w));
			}

			inline vec4& operator= (const vec4& other) {
				load(other.x, other.y, other.z, other.w);
				return *this;
			}
			inline const vec4 operator - () const {
				return vec4(-x, -y, -z, -w);
			}
			inline const vec4 operator+(const vec4& other) const {
				return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
			}
			inline const vec4 operator-(const vec4& other) const {
				return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
			}
			inline const vec4 operator*(const vec4& other) const {
				return vec4(x * other.x, y * other.y, z * other.z, w * other.w);
			}
			inline const vec4 operator*(const float s) const {
				return vec4(x * s, y * s, z * s, w * s);
			}
			inline friend const vec4 operator*(const float s, const vec4& other) {
				return other * s;
			}
			inline const vec4 operator/(const float s) const {
			#ifdef _DEBUG
				if (fabs(s) < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

				float r = 1.0f / s;
				return *this * r;
			}

			inline vec4& operator += (const vec4& other) {
				return add(other);
			}
			inline vec4& operator -= (const vec4& other) {
				return subtract(other);
			}
			inline vec4& operator *= (const vec4& other) {
				return multiply(other);
			}
			inline vec4& operator /= (const float s) {
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

			inline bool operator==(const vec4& other) const {
				return x == other.x && y == other.y && z == other.z && w == other.w;
			}
			inline bool operator!=(const vec4& other) const {
				return x != other.x || y != other.y || z != other.z || w != other.w;
			}

			inline operator const float* () const {
				return static_cast<const float*>(&x);
			}
			inline operator float* () {
				return static_cast<float*>(&x);
			}


			inline friend std::ostream& operator<<(std::ostream& stream, const vec4& vector) {
				stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";

				return stream;
			}
		};
	}
}

#endif // !_VECTOR_H