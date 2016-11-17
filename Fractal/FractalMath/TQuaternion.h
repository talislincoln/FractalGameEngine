#ifndef _TQUATERNION_H
#define _TQUATERNION_H

#include "Vector.h"

namespace fractal {
	namespace fmath {
		struct TQuaternion : public Vector4 {

			Vector3 vector;

			inline TQuaternion(float s = 0)
			{
				x = s;
				y = s;
				z = s;
				w = s;

				vector.load(s, s, s);
			}

			inline TQuaternion(float w, const Vector3 &v) {
				this->w = w;
				x = v.x;
				y = v.y;
				z = v.z;
				vector.load(x, y, z);
			}

			inline TQuaternion(float w, float x, float y, float z) {
				this->w = w;
				this->x = x;
				this->y = y;
				this->z = z;

				vector.load(x, y, z);
			}

			inline TQuaternion(const Vector4& v) {
				w = v.w;
				x = v.x;
				y = v.y;
				z = v.z;
			}

			inline TQuaternion(const TQuaternion& q) {
				w = q.w;
				x = q.x;
				y = q.y;
				z = q.z;

				vector.load(x, y, z);
			}

			inline const TQuaternion conjugate() const {
				return TQuaternion(w, -this->vector);
			}

			inline const TQuaternion inverse() const {
				float magnitudesquare = x*x + y*y + z*z + w*w;
				return this->conjugate()/ magnitudesquare;
			}

			inline const TQuaternion operator*(const TQuaternion& q) const {
				return TQuaternion(this->w * q.w - this->vector.dot(q.vector),
					q.vector*this->w + this->vector*q.w + this->vector.cross(q.vector));
			}
		};
	}
}
#endif // !_TQUATERNION_H
