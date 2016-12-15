#include "shapes\PhysicsBox.h"

namespace fractal {
	namespace fphysics {
		using namespace fmath;
		PhysicsBox::PhysicsBox(const Vector3 boxVector) :
			PhysicsShape() {
			this->boxVector = boxVector;
			shape = BOX;
		}

		void PhysicsBox::calMass(massData* md) const {

			float ex2 = float(4.0) * boxVector.x * boxVector.x;
			float ey2 = float(4.0) * boxVector.y * boxVector.y;
			float ez2 = float(4.0) * boxVector.z * boxVector.z;
			float mass = float(8.0) * boxVector.x * boxVector.y * boxVector.z * density;
			float x = float(1.0 / 12.0) * mass * (ey2 + ez2);
			float y = float(1.0 / 12.0) * mass * (ex2 + ez2);
			float z = float(1.0 / 12.0) * mass * (ex2 + ey2);
			Matrix3 I = Matrix3(x, y, z);

			// Transform tensor to local space
			I = local.rotation.toMatrix3() * I * Matrix3::transpose((local.rotation.toMatrix3()));
			Matrix3 identity;
			identity.loadIdentity();
			I += (identity * local.position.dot(local.position) - Matrix3::outerProduct(local.position, local.position)) * mass;

			md->center = local.position;
			md->inertia = I;
			md->mass = mass;
		}
		void PhysicsBox::setAABB(const Transform& tx, AABB* aabb) {

			Matrix4 world = tx * (local);

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
			{
				p[i] = world * p[i];
				aabb->min = fmath::getMin(aabb->min, p[i]);
				aabb->max = fmath::getMax(aabb->max, p[i]);
			}
		}

		std::vector<Point3> PhysicsBox::getVertices() {
			std::vector<Point3> Vertices;
			Point3 vertice;

			vertice = Point3(-boxVector.x, -boxVector.y, -boxVector.z);
			Vertices.push_back(vertice);
			vertice = Point3(-boxVector.x, -boxVector.y, boxVector.z);
			Vertices.push_back(vertice);
			vertice = Point3(-boxVector.x, boxVector.y, -boxVector.z);
			Vertices.push_back(vertice);
			vertice = Point3(-boxVector.x, boxVector.y, boxVector.z);
			Vertices.push_back(vertice);
			vertice = Point3(boxVector.x, -boxVector.y, -boxVector.z);
			Vertices.push_back(vertice);
			vertice = Point3(boxVector.x, -boxVector.y, boxVector.z);
			Vertices.push_back(vertice);
			vertice = Point3(boxVector.x, boxVector.y, -boxVector.z);
			Vertices.push_back(vertice);
			vertice = Point3(boxVector.x, boxVector.y, boxVector.z);
			Vertices.push_back(vertice);

			return Vertices;
		}

	}
}
