#include "shapes\PhysicsSphere.h"

namespace fractal {
	namespace fphysics {
		using namespace fmath;
		PhysicsSphere::PhysicsSphere(Point3 center, float r) :
			PhysicsShape() {
			this->center = center;
			this->radius = r;
 			shape = SPHERE;
		}

		void PhysicsSphere::calMass(massData* md) const {

			float r2 = radius * radius;
			float mass = float(8.0) * r2 * M_PI * density;

			Matrix3 I = Matrix3(float(2.0 / 5.0) * mass * (r2));

			// Transform tensor to local space
			I = local.rotation.toMatrix3() * I * Matrix3::transpose((local.rotation.toMatrix3()));
			Matrix3 identity;
			identity.loadIdentity();
			I += (identity * local.position.dot(local.position) - Matrix3::outerProduct(local.position, local.position)) * mass;

			md->center = local.position;
			md->inertia = I;
			md->mass = mass;
		}
		void PhysicsSphere::setAABB(const Transform& tx, AABB* aabb) {

			Matrix4 world = tx * (local);
				aabb->min = world * Point3(-radius);
				aabb->max = world * Point3(radius);
		}

	}
}
