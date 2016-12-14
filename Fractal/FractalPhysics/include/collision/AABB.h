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
			inline AABB& operator = (const fphysics::AABB& other)
			{
				this->max = other.max;
				this->min = other.min;
				return *this;
			}

		};

	}
}


#endif // !_AABB_H