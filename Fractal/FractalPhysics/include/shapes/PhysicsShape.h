#ifndef _PHYSICS_SHAPE
#define _PHYSICS_SHAPE
#include <FractalMath\Matrix.h>
#include "collision\AABB.h"
#include "Transform.h"
#include "PhysicsDefine.h"
namespace fractal {
	namespace fphysics {

		class PhysicsShape
		{
			public :
			PhysicsShape( float friction = float(0.4), float restitution = float(0.2), float density = float(1.0));
			~PhysicsShape();

			inline void SetFriction(const float friction) {
				this->friction = friction;
			}
			inline void SetRestitution(const float restitution) {
				this->restitution = restitution;
			}
			inline void SetDensity(const float density) {
				this->density = density;
			}
			virtual void calMass(massData* md) const = 0;
			virtual void setAABB(const Transform& tx, AABB* aabb) = 0;
			//fmath::Vector3 boxVector; // from center of mass
			// point3/*maybe?*/ and float r for circle;
			// Vector3 and float r for caps
		protected:
			Transform* localPosition;
			float friction;
			float restitution;
			float density;
			Shape shape;
			AABB aabb;

			friend class PhysicsShapeComponent;
		};
	}
}
#endif // !_SHAPE_COMPONENT
