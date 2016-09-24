#include "Vector.h"
#include <iostream>
namespace fractal {
	namespace fmath {
		#ifndef VERY_SMALL
		#define VERY_SMALL 1.0e-7f
		#endif

#pragma region VEC2
		vec2::vec2(float x, float y) {
			this->x = x;
			this->y = y;
		}
#pragma endregion VEC2


#pragma region VEC3
		vec3::vec3(float s /* = 0 */) {
			load(s, s, s);
		}

		vec3::vec3(const float x, const float y, const float z) {
			load(x, y, z);
		}

		vec3::vec3(const vec3& v) {
			load(v.x, v.y, v.z);
		}

		void vec3::load(const float x, const float y, const float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vec3& vec3::add(const vec3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		vec3& vec3::subtract(const vec3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		vec3& vec3::multiply(const vec3& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		float vec3::dot(const vec3& other) {
			return x * other.x + y * other.y + z * other.z;
		}

		const vec3 vec3::cross(const vec3& other) {
			return vec3(y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x);
		}

		vec3& vec3::normalize() {
			const float magnitude = this->magnitude();
			#ifdef _DEBUG 
				if (magnitude < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

			return *this /= magnitude;
		}

		const float vec3::magnitude() {
			return float(sqrt(x * x + y * y + z * z));
		}

		vec3& vec3::operator= (const vec3& other) {
			load(other.x, other.y, other.z);
			return *this;
		}

		const vec3 vec3::operator - () const {
			return vec3(-x, -y, -z);
		}

		const vec3 vec3::operator+(const vec3& other) const {
			return vec3(x + other.x, y + other.y, z + other.z);
		}

		const vec3 vec3::operator-(const vec3& other) const {
			return vec3(x - other.x, y - other.y, z - other.z);
		}

		const vec3 vec3::operator*(const vec3& other) const {
			return vec3(x * other.x, y * other.y, z * other.z);
		}

		const vec3 vec3::operator*(const float s) const {
			return vec3(s*x, s*y, s*z);
		}

		const vec3 operator*(const float s, const vec3& other) {
			return other * s;
		}

		const vec3 vec3::operator / (const float s) const {
			#ifdef _DEBUG
				if (fabs(s) < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

			float r = 1.0f / s;
			return *this * r;
		}

		vec3& vec3::operator+= (const vec3& other) {
			return add(other);
		}

		vec3& vec3::operator-= (const vec3& other) {
			return subtract(other);
		}

		vec3& vec3::operator*= (const vec3& other) {
			return multiply(other);
		}

		vec3& vec3::operator/=(const float s) {
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

		bool vec3::operator==(const vec3& other) const {
			return x == other.x && y == other.y && z == other.z;
		}

		bool vec3::operator!=(const vec3& other) const {
			return x != other.x || y != other.y || z != other.z;
		}

		const float vec3::operator[] (int index) const {
			return *(&x + index);
		}

		float& vec3::operator [] (int index) {
			return *(&x + index);
		}

		vec3::operator const float* () const {
			return static_cast<const float*>(&x);
		}

		vec3::operator float* () {
			return static_cast<float*>(&x);
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";

			return stream;
		}
#pragma endregion VEC3

#pragma region VEC4
		vec4::vec4(const float s) {
			load(s, s, s, s);
		}

		vec4::vec4(const float x, const float y, const float z, const float w) {
			load(x, y, z, w);
		}

		vec4::vec4(const vec3& other) {
			load(other.x, other.y, other.z, 1.0f);
		}

		vec4::vec4(const vec4& other) {
			load(other.x, other.y, other.z, other.w);
		}

		void vec4::load(const float x, const float y, const float z, const float w) {
			vec3::load(x, y, z);
			this->w = w;
		}

		vec4& vec4::add(const vec4& other) {
			add(other);
			w += other.w;
			return *this;
		}

		vec4& vec4::subtract(const vec4& other) {
			subtract(other);
			w -= other.w;
			return *this;
		}

		vec4& vec4::multiply(const vec4& other) {
			multiply(other);
			w *= other.w;
			return *this;
		}

		float vec4::dot(const vec3& other) {
			return x * other.x + y * other.y + z * other.z + w * 1;
		}

		float vec4::dot(const vec4& other) {
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		vec4& vec4::normalize() {
			const float magnitude = this->magnitude();
			#ifdef _DEBUG 
				if (magnitude < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

			return *this /= magnitude;
		}

		const float vec4::magnitude() {
			return float(sqrt(x * x + y * y + z * z + w * w));
		}

		inline vec4& vec4::operator= (const vec4& other) {
			load(other.x, other.y, other.z, other.w);
			return *this;
		}

		const vec4 vec4::operator-() const {
			return vec4(-x, -y, -z, -w);
		}

		const vec4 vec4::operator+(const vec4& other) const {
			return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		const vec4 vec4::operator-(const vec4& other) const {
			return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		const vec4 vec4::operator*(const vec4& other) const {
			return vec4(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		const vec4 vec4::operator*(const float s) const {
			return vec4(x * s, y * s, z * s, w * s);
		}

		const vec4 operator*(const float s, const vec4& other) {
			return other * s;
		}

		const vec4 vec4::operator/(const float s) const {
			#ifdef _DEBUG
				if (fabs(s) < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

			float r = 1.0f / s;
			return *this * r;
		}

		vec4& vec4::operator += (const vec4& other) {
			return add(other);
		}

		vec4& vec4::operator -= (const vec4& other) {
			return subtract(other);
		}

		vec4& vec4::operator *= (const vec4& other) {
			return multiply(other);
		}

		vec4& vec4::operator /= (const float s) {
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

		bool vec4::operator==(const vec4& other) const {
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool vec4::operator!=(const vec4& other) const {
			return x != other.x || y != other.y || z != other.z || w != other.w;
		}

		vec4::operator const float* () const {
			return static_cast<const float*>(&x);
		}

		vec4::operator float* () {
			return static_cast<float*>(&x);
		}

		std::ostream& operator<<(std::ostream& stream, const vec4& vector) {
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";

			return stream;
		}
#pragma endregion VEC4
	}
}