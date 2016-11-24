#include "PhysicsBody.h"


namespace fractal {
	namespace fphysics {
		PhysicsBody::PhysicsBody() {

			m_linearVelocity.load();
			m_angularVelocity.load();
			m_transform.load();
			m_gravityScale = float(1.0);
			m_layers = 0x000000001;
			m_linearDamping = float(0.0);
			m_angularDamping = float(0.1);
			m_force.load();
			m_torque.load();
			m_sleepTime = float(0.0);
			m_flags = 0x000000000;
			m_flags |= DYNAMIC;
			m_flags |= ALLOWSLEEP;
			m_flags |= AWAKE;
			m_flags |= ACTIVE;
		}

		void PhysicsBody::calculateMassData() {

			Matrix3 inertia = Matrix3((0.0f));
			m_inverseInertiaModel = Matrix3((0.0f));
			m_inverseInertiaWorld = Matrix3((0.0f));
			m_inverseMass = (0.0f);
			m_mass = (0.0f);
			float mass = (0.0f);

			if (m_flags & STATIC || m_flags &KINEMATIC)
			{
				m_localCenter.load();
				m_worldCenter = m_transform.position;
				return;
			}

			Vector3 lc;
			lc.load();
			/* need vector of all component to countiun
			for (PhysicsShapeComponent* shapes = m_boxes; box; box = box->next)
			{
			if (box->density == float(0.0))
			continue;

			massData md;
			box->calMass(&md);
			mass += md.mass;
			inertia += md.inertia;
			lc += md.center * md.mass;
			}

			if (mass > float(0.0))
			{
			m_mass = mass;
			m_inverseMass = float(1.0) / mass;
			lc *= m_inverseMass;
			Matrix3 identity;
			Matrix3 outerP = Matrix3::outerProduct(lc, lc);
			identity.loadIdentity();
			inertia -= (identity * lc.dot(lc) - outerP) * mass;
			m_inverseInertiaModel = inertia;

			bool freezeX = false, freezeY = false, freezeZ = false;
			if (m_flags & eLockAxisX)
			freezeX = true;

			if (m_flags & eLockAxisY)
			freezeY = true;

			if (m_flags & eLockAxisZ)
			freezeZ = true;
			m_inverseInertiaModel.freezeRotate(freezeX, freezeY, freezeZ);
			}
			else
			{
			// Force all dynamic bodies to have some mass
			m_inverseMass = float(1.0);
			m_inverseInertiaModel = Matrix3(0.0f);
			m_inverseInertiaWorld = Matrix3(0.0f);
			}

			m_localCenter = lc;
			m_worldCenter = m_tx * (Point3)lc;

			*/
		}

	}

}