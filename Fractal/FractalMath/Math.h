#ifndef _FMATH_H
#define _FMATH_H
#include "Vector.h"
#include <cmath>

namespace fractal {
	namespace fmath {
		#ifndef F_PI
		#define F_PI 3.14159265358979323846f
		#endif

		#ifndef DEGREES_TO_RADIANS
		#define DEGREES_TO_RADIANS (F_PI / 180.0f)
		#endif	

		inline float toRadians(float degrees) {
			return degrees * DEGREES_TO_RADIANS;
		}

		//change this to a vec4 and use the right overloaded functions
		struct Sphere : public Vector3 {
			float r;
			Sphere(float s = 0.0f) { x = s; y = s; z = s; r = s; }

			Sphere(float x, float y, float z, float r) {
				this->x = x; this->y = y; this->z = z; this->r = r;
			}

			inline Sphere(const Sphere& v) {
				x = v.x;  y = v.y;  z = v.z; r = v.r;
			}
		};

		//change this implementation to a vec4 and use the proper overloaded functions
		struct Plane : public Vector3 {
			float d;

			/// Here's a set of constructors
			inline Plane(float s = 0.0f) {
				x = s;
				y = s;
				z = s;
				d = s;
			}
			inline Plane(float x, float y, float z, float d) {
				this->x = x;
				this->y = y;
				this->z = z;
				this->d = d;
			}

			inline Plane(const Plane& v) {
				x = v.x;
				y = v.y;
				z = v.z;
				d = v.d;
			}

			//normalized equation of a plane
			inline Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) {
				Vector3 a = v1 - v0;
				Vector3 b = v2 - v0;

				//make a cross product
				Vector3 n = Vector3(a.y * b.z - a.z * b.y,
					a.z * b.x - a.x * b.z,
					a.x * b.y - a.y * b.x);
				float magnitude = float(sqrt(n.x * n.x + n.y * n.y + n.z * n.z));

				//normalized plane
				Plane(x / magnitude, y / magnitude, z / magnitude, a.x * b.x + a.y * b.y + a.z * b.z);
			}

			inline void normalize() {
				float a = sqrt(x*x + y*y + z*z);
				x /= a;
				y /= a;
				z /= a;
				d /= a;
			}
		};
	}
}



#endif // !_FMATH_H
