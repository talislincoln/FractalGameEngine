#ifndef _PHYSICS_SHAPE
#define _PHYSICS_SHAPE
#include <FractalMath\Matrix.h>
#include <FractalPhysics\include\collision\AABB.h>
#include <FractalPhysics\include\Transform.h>
#include <FractalPhysics\include\PhysicsDefine.h>
<<<<<<< HEAD
#include <vector>
=======
namespace fractal {
	namespace fphysics {

		class PhysicsShape
		{
			public :
			PhysicsShape( float friction = float(0.995), float restitution = float(0.2), float density = float(1.0));
			~PhysicsShape();

			inline void SetFriction(const float friction) {
				this->friction = friction;
			}
			inline void SetRestitution(const float restitution) {
				this->restitution = restitution;
			}
			inline float getDensity() {
				return this->density;
			}
			inline float getFriction() {
				return this->friction;
			}
			inline float getRestitution() {
				return this->restitution;
			}
			inline void SetDensity(const float density) {
				this->density = density;
			}
			inline void setLocalTransform(fmath::Vector3 position = Vector3(), fmath::Quaternion rotation = fmath::Quaternion(), fmath::Vector3 scale = fmath::Vector3(1)) {
				local.position = position;
				local.rotation = rotation;
				local.scale = scale;
			}
			virtual std::vector<Point3> getVertices()=0;
			virtual void calMass(massData* md) const = 0;
			virtual void setAABB(const Transform& tx, AABB* aabb) = 0;
			//fmath::Vector3 boxVector; // from center of mass
			// point3/*maybe?*/ and float r for circle;
			// Vector3 and float r for caps
		protected:
			Transform local;
			float friction;
			float restitution;
			float density;
			Shape shape;
			AABB aabb;

			friend class PhysicsBody;
			friend class PhysicsShapeComponent;
		};
	}
}
#endif // !_SHAPE_COMPONENT
