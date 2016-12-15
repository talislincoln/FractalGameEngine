#ifndef _PHYSICS_BOX_H
#define _PHYSICS_BOX_H

#include <FractalMath\Vector.h>
#include <FractalPhysics\include\collision\AABB.h>
#include <FractalPhysics\include\Transform.h>
#include "PhysicsShape.h"
namespace fractal {
	namespace fphysics {


		class PhysicsSphere : public PhysicsShape {
		public:
			PhysicsSphere(fmath::Point3 center = Vector3(0), const float radius = 0.5f);
			fmath::Vector3 center; // from center of mass
			float radius;



			void calMass(massData* md) const;
			void setAABB(const Transform& tx, AABB* aabb);
		};

	}
}

#endif // !_BOX_H