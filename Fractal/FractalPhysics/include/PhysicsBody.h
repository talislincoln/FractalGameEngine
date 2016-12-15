#ifndef _PHYSICS_BODY
#define _PHYSICS_BODY
#include "collision\AABB.h"
#include <vector>
#include <FractalMath\Quaternion.h>
#include "shapes\PhysicsShape.h"
#include "Transform.h"
namespace fractal {
	namespace fphysics {

		class PhysicsBody{
		public:
			PhysicsBody();
			void calculateMassData(const std::vector<PhysicsShape*> shapeList, Transform& m_localTransform);

		private:
			//m_flages
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
			fmath::Quaternion m_quaternion;
			fmath::Vector3 m_localCenter;
			fmath::Vector3 m_worldCenter;
			float m_gravityScale;
			int m_flags;
			float m_sleepTime;
			//Body* m_next;
			//Body* m_prev;

			float m_linearDamping;
			float m_angularDamping;

			friend class PhysicsShapeComponent;
			friend class PhysicsBodyComponent;
			friend class PhysicsWorld;
		};

	}
}

#endif // !m_PHYSICSm_BODY
