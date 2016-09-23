#ifndef _FMATH_H
#define _FMATH_H
#include "Vector.h"

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
	}
}



#endif // !_FMATH_H
