#ifndef _PHYSICS_BODY_COMPONENT
#define _PHYSICS_BODY_COMPONENT

#include <Fractal\include\scene\Component.h>
#include <FractalPhysics\include\PhysicsBody.h>
#include <FractalPhysics\include\collision\AABB.h>
#include <FractalPhysics\include\Transform.h>
#include <string>
#include <vector>
namespace fractal {
	namespace fscene {
		class TransformComponent;
	}
	namespace fphysics {
		class PhysicsBodyComponent :
			public fscene::Component
		{
		public:
			PhysicsBodyComponent::PhysicsBodyComponent(PhysicsBody* bodyDef, const std::string& name = "");
			virtual ~PhysicsBodyComponent();


			bool initialize();
			void update();
			bool shutdown();


			//apply
			inline void reset() {
				m_body->m_force.load();
			}
			inline void ApplyLinearForce(const Vector3& force) {
				m_body->m_force += force * m_body->m_mass;
				SetToAwake();
			}
			inline void ApplyTorque(const Vector3& torque) {
				m_body->m_torque = torque;
				SetToAwake();

			}
			inline void ApplyLinearImpulse(const Vector3& impulse) {
				m_body->m_linearVelocity += impulse * m_body->m_inverseMass;
				SetToAwake();
			}
			inline void ApplyForceAtWorldPoint(const Vector3& force, const Point3& point) {
				m_body->m_force += force * m_body->m_mass;
				m_body->m_torque += (point - m_body->m_worldCenter).cross(force);
				SetToAwake();
			}
			inline void ApplyLinearImpulseAtWorldPoint(const Vector3& impulse, const Point3& point) {
				m_body->m_linearVelocity += impulse * m_body->m_inverseMass;
				m_body->m_angularVelocity += m_body->m_inverseInertiaWorld * (point - m_body->m_worldCenter).cross( impulse);
			}

			//set
			inline void SetGravityScale(float scale) {
				m_body->m_gravityScale = scale;
				SetToAwake();
			}
			// get
			inline float GetGravityScale() const { return m_body->m_gravityScale; }
			inline const Vector3 GetLinearVelocity() const { return m_body->m_linearVelocity; }
			inline const Vector3 GetAngularVelocity() const { return m_body->m_angularVelocity; }
			inline float GetMass() const { return m_body->m_mass; }
			inline bool IsAwake() const { return m_body->m_flags & PhysicsBody::AWAKE ? true : false; }
			inline int GetFlags() const { return m_body->m_flags; }
			//const Point3 GetLocalPoint(const Point3& p) const { return m_body->m_lo}
			//const Vector3 GetLocalVector(const Vector3& v) const ;
			//const Vector3 GetWorldPoint(const Point3& p) const;
			//const Vector3 GetWorldVector(const Vector3& v) const;
			//const Vector3 GetVelocityAtWorldPoint(const Point3& p) const;
			inline void SetLinearVelocity(const Vector3& v) {
				if (m_body->m_flags & PhysicsBody::STATIC)
					//assert(false);
					return;
				if (v.dot(v) > float(0.0))
				{
					SetToAwake();
				}
				m_body->m_linearVelocity = v;

				SetToAwake();
			}
			inline void SetAngularVelocity(const Vector3 v) {
				m_body->m_angularVelocity = v;

				SetToAwake();
			}
			inline void setGround(bool ground) {
				m_isGround = ground;
			}
			inline bool isGround() {
				return m_isGround;
			}
			inline void SetToAwake() {
				if (!(m_body->m_flags & PhysicsBody::AWAKE))
				{
					m_body->m_flags |= PhysicsBody::AWAKE;
					m_sleepTime = float(0.0);
				}
			}
			inline float getFriction() {
				return shapes[0]->getFriction();
			}
			inline void SetToSleep() {

				m_body->m_flags &= ~PhysicsBody::AWAKE;
				m_sleepTime = float(0.0);
				m_body->m_linearVelocity.load();
				m_body->m_angularVelocity.load();
				m_body->m_force.load();
				m_body->m_torque.load();
			}
			/*inline void SetTransform(const Vector3& position) {
				m_physicsTransform.position = position;

				SetToAwake();
			}
			inline void SetTransform(const Vector3& position, const Vector3& axis, float angle) {
				m_physicsTransform.position = position;
				m_physicsTransform.rotation = Quaternion(angle, axis);

				SetToAwake();
			}
*/
		private:
			bool m_isGround;
			bool m_checkMass;
			float m_sleepTime;
			PhysicsBody* m_body;
			//Transform m_physicsTransform;

			PhysicsWorld* physicsWorld;

			fscene::GameObject* parent;
			fscene::TransformComponent* transform;
			std::vector<PhysicsShape*> shapes;

			friend class PhysicsWorld;
			friend class PhysicsShapeComponent;
		};
	}
}


/* TODO:

//void SetLinearDamping(float damping);
//float GetLinearDamping(float damping) const;
//void SetAngularDamping(float damping);
//float GetAngularDamping(float damping) const;
//const q3Transform GetTransform() const;
//void getParentTransform();

//const q3Quaternion GetQuaternion() const;


*/

#endif // !_BODY_COMPONENT