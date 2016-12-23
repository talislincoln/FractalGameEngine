#include "collision\AABB.h"


namespace fractal {
	namespace fphysics {
		AABB::AABB() :
			max(-MAX_FLOAT),
			min(MAX_FLOAT)
		{
		}


		AABB::~AABB()
		{
		}

	}
}