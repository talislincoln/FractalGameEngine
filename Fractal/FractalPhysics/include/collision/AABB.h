#ifndef _AABB_H
#define _AABB_H

#include <FractalMath\Vector.h>

namespace fractal {
	namespace fphysics {
		struct AABB
		{
		public:
			AABB();
			~AABB();
			fmath::Point3 max;
			fmath::Point3 min;
		};
	}
}


#endif // !_AABB_H