#ifndef _PHYSICS_BOX_H
#define _PHYSICS_BOX_H

#include <FractalMath\Vector.h>
#include <FractalPhysics\include\collision\AABB.h>
#include <FractalPhysics\include\Transform.h>
#include "PhysicsShape.h"
namespace fractal {
	namespace fphysics {


		class PhysicsBox : public PhysicsShape {
		public:
			PhysicsBox(const fmath::Vector3 boxVector = Vector3(0.1f));
			fmath::Vector3 boxVector; // from center of mass
			
			

			virtual std::vector<Point3>getVertices();
			void calMass(massData* md) const;
			void setAABB(const Transform& tx, AABB* aabb);
		};

	}
}

#endif // !_BOX_H