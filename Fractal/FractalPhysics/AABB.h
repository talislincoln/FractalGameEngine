#ifndef _AABB_H
#define _AABB_H

#include <FractalMath\Vector.h>

namespace fractal {
	class AABB
	{
	public:
		AABB();
		~AABB();
		fmath::Point3 max;
		fmath::Point3 min;
	private:
	};
}


#endif // !_AABB_H