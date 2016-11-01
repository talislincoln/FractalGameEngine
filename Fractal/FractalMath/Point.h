#ifndef _POINT_H
#define _POINT_H
#include <iostream>

#ifndef VERY_SMALL
#define VERY_SMALL 1.0e-7f
#endif
namespace fractal {
	namespace fmath {
		struct Point3 {
			float x, y, z;

			inline Point3(float s = 0.0f) {
				load(s, s, s);
			}

			inline Point3(float x, float y, float z) {
				load(x, y, z);
			}
			
			inline Point3(const Point3& p) {
				load(p.x, p.y, p.z);
			}

			inline void load(float x, float y, float z) {
				this->x = x;
				this->y = y;
				this->z = z;
			}


			inline Point3& add(const Point3& other) {
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}

			inline Point3& subtract(const Point3& other) {
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}

			inline Point3& multiply(const Point3& other) {
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}
			inline const Point3 operator+(const Point3& other) const {
				return Point3(x + other.x, y + other.y, z + other.z);
			}

			inline const Point3 operator-(const Point3& other) const {
				return Point3(x - other.x, y - other.y, z - other.z);
			}

			inline const Point3 operator*(const Point3& other) const {
				return Point3(x * other.x, y * other.y, z * other.z);
			}

			inline const Point3 operator*(const float s) const {
				return Point3(s*x, s*y, s*z);
			}

			inline Point3& operator= (const Point3& other) {
				load(other.x, other.y, other.z);
				return *this;
			}

			inline const Point3 operator/(const float s) const {
			#ifdef _DEBUG
				if (fabs(s) < VERY_SMALL) {
					std::string errorMsg("Divide by nearly zero! ");
					throw errorMsg;
				}
			#endif

				float r = 1.0f / s;
				return *this * r;
			}
			inline const Point3 operator - () const {
				return Point3(-x, -y, -z);
			}

			inline friend const Point3 operator*(const float s, const Point3& other) {
				return other * s;
			}

			inline Point3& operator+=(const Point3& other) {
				return add(other);
			}
			inline Point3& operator-=(const Point3& other) {
				return subtract(other);
			}
			inline Point3& operator*=(const Point3& other) {
				return multiply(other);
			}
			inline Point3& operator/=(const float s) {

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

			inline bool operator==(const Point3& other) const {
				return x == other.x && y == other.y && z == other.z;
			}
			inline bool operator!=(const Point3& other) const {
				return x != other.x || y != other.y || z != other.z;
			}

			inline operator const float* () const {
				return static_cast<const float*>(&x);
			}

			inline operator float* () {
				return static_cast<float*>(&x);
			}
			inline friend std::ostream& operator<<(std::ostream& stream, const Point3& point) {
				stream << "(" << point.x << ", " << point.y << ", " << point.z << ")";

				return stream;
			}
		};
	}
}

#endif // !_POINT_H
