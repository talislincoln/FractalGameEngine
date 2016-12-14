#ifndef _AABB_COLISION
#define _AABB_COLISION

#include "AABB.h"
#include <FractalMath\Vector.h>
namespace fractal {
	namespace fphysics {
		class AABBCollision
		{
		public:
			AABBCollision();
			~AABBCollision();

			static inline bool isCollide(const AABB& a,const AABB& b) {
				return(a.max.x > b.min.x && a.min.x < b.max.x &&
					a.max.y > b.min.y && a.min.y < b.max.y &&
					a.max.z > b.min.z && a.min.z < b.max.z);
			}
			static inline bool isCollide(AABB& a, fmath::Point3 p) {
				return(p.x > a.min.x && p.x < a.max.x &&
					p.y > a.min.y && p.y < a.max.y &&
					p.z > a.min.z && p.z < a.max.z);
			}

			static inline bool isCollide( fmath::Point3 p, AABB& a) {
				return(p.x > a.min.x && p.x < a.max.x &&
					p.y > a.min.y && p.y < a.max.y &&
					p.z > a.min.z && p.z < a.max.z);
			}
		};
	}
}
#endif // !_AABB_COLISION

