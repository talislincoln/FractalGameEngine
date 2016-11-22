#ifndef _PHYSICS_BODY
#define _PHYSICS_BODY
#include "collision\AABB.h"
#include <FractalMath\Quaternion.h>
#include "Transform.h"
namespace fractal {
	namespace fphysics {

		class PhysicsBody {

		public:
			PhysicsBody();
			//m_flages
			void getParentTransform();
		private:

			enum
			{
				AWAKE = 0x001,
				ACTIVE = 0x002,
				ALLOWSLEEP = 0x004,
				ISLAND = 0x010,
				STATIC = 0x020,
				DYNAMIC = 0x040,
				KINEMATIC = 0x080,
				LOCKAXISX = 0x100,
				LOCKAXISY = 0x200,
				LOCKAXISZ = 0x400,
			};
			AABB m_aabb;
			fmath::Matrix3 m_inverseInertiaModel;
			fmath::Matrix3 m_inverseInertiaWorld;
			float m_mass;
			float m_inverseMass;
			fmath::Vector3 m_linearVelocity;
			fmath::Vector3 m_angularVelocity;
			fmath::Vector3 m_force;
			fmath::Vector3 m_torque;
			Transform m_transform;
			fmath::Quaternion m_quaternion;
			fmath::Vector3 m_localCenter;
			fmath::Vector3 m_worldCenter;
			float m_sleepTime;
			float m_gravityScale;
			int m_layers;
			int m_flags;

			//Body* m_next;
			//Body* m_prev;

			float m_linearDamping;
			float m_angularDamping;

			//q3ContactEdge* m_contactList;

			//friend class q3scene;
			//friend struct q3Manifold;
			//friend class q3ContactManager;
			//friend struct q3Island;
			//friend struct q3Contactsolver;

			//Body(const DefaultBody& def, q3scene* scene);

			void calculateMassData();
			//void synchronizeProxies();

			friend class PhysicsShapeComponent;
			friend class PhysicsWorld;
		};

	}
}

#endif // !_PHYSICS_BODY
