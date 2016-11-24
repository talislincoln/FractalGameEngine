#ifndef _PHYSICS_BOX_H
#define _PHYSICS_BOX_H

#include <FractalMath\Vector.h>
#include "Transform.h"
#include "collision\AABB.h"
#include "PhysicsShape.h"
namespace fractal {
	namespace fphysics {


		class PhysicsBox : public PhysicsShape {
			PhysicsBox(fmath::Vector3 boxVector = Vector3(1));
			fmath::Vector3 boxVector; // from center of mass

			void calMass(massData* md) const;
			void setAABB(const Transform& tx, AABB* aabb);
		};

	}
}

#endif // !_BOX_H