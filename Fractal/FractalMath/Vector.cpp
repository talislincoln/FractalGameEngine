#include "Vector.h"
#include <iostream>
namespace fractal {
	namespace fmath {
		vec2::vec2(float x, float y) {
			this->x = x;
			this->y = y;
		}

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

		/*vec3& vec3::divide(const vec3& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}*/

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

		vec3 operator*(const float s, const vec3& other) {
			return other * s;
		}

		const vec3 vec3::operator / (const float s) const {
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

		/*vec3& vec3::operator/= (const vec3& other) {
			return divide(other);
		}*/

		const float vec3::operator[] (int index) const {
			return *(&x + index);
		}

		float& vec3::operator [] (int index) {
			return *(&x + index);
		}

		bool vec3::operator==(const vec3& other) const {
			return x == other.x && y == other.y && z == other.z;
		}

		bool vec3::operator!=(const vec3& other) const {
			return x != other.x || y != other.y || z != other.z;
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
	}
}