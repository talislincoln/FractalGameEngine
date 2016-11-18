#include "Box.h"

namespace fractal {
	namespace fphysics {
		Box::Box(Vector3 boxVector) :
			PhysicsShape() {
			this->boxVector = boxVector;
			shape = BOX;
		}

		void Box::calMass(massData* md) const {

			float ex2 = float(4.0) * boxVector.x * boxVector.x;
			float ey2 = float(4.0) * boxVector.y * boxVector.y;
			float ez2 = float(4.0) * boxVector.z * boxVector.z;
			float mass = float(8.0) * boxVector.x * boxVector.y * boxVector.z * density;
			float x = float(1.0 / 12.0) * mass * (ey2 + ez2);
			float y = float(1.0 / 12.0) * mass * (ex2 + ez2);
			float z = float(1.0 / 12.0) * mass * (ex2 + ey2);
			Matrix3 I = Matrix3(x, y, z);

			// Transform tensor to local space
			I = localPosition->rotate.toMatrix3() * I * Matrix3::transpose((localPosition->rotate.toMatrix3()));
			Matrix3 identity;
			identity.loadIdentity();
			I += (identity * localPosition->position.dot(localPosition->position) - Matrix3::outerProduct(localPosition->position, localPosition->position)) * mass;

			md->center = localPosition->position;
			md->inertia = I;
			md->mass = mass;
		}
		void Box::setAABB(const Transform& tx, AABB* aabb) {

			Transform world = tx * (*localPosition);

			Point3 p[8];
			p[0] = Point3(-boxVector.x, -boxVector.y, -boxVector.z);
			p[1] = Point3(-boxVector.x, -boxVector.y, boxVector.z);
			p[2] = Point3(-boxVector.x, boxVector.y, -boxVector.z);
			p[3] = Point3(-boxVector.x, boxVector.y, boxVector.z);
			p[4] = Point3(boxVector.x, -boxVector.y, -boxVector.z);
			p[5] = Point3(boxVector.x, -boxVector.y, boxVector.z);
			p[6] = Point3(boxVector.x, boxVector.y, -boxVector.z);
			p[7] = Point3(boxVector.x, boxVector.y, boxVector.z);

			for (int i = 0; i < 8; i++)
				p[i] = world * p[i];

			Vector3 min(FLT_MAX, FLT_MAX, FLT_MAX);
			Vector3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

			for (int i = 0; i < 8; i++)
			{
				min = fmath::getMin(min, p[i]);
				max = fmath::getMax(max, p[i]);
			}

			aabb->min = min;
			aabb->max = max;
		}

	}
}
