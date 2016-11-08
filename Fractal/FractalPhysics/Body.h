#pragma once
#include <FractalMath\Math.h>
#include <FractalMath\Matrix.h>
#include "Component.h"
#include "Transform.h"
namespace fractal {
	using namespace fmath;
	enum BodyType
	{
		StaticBody,
		DynamicBody,
		KinematicBody
	};

	class Body : public Component
	{
	public:
		~Body(); 
		//const q3Box* AddBox(const q3BoxDef& def);

		// Removes this box from the body and broadphase. Forces the body
		// to recompute its mass if the body is dynamic. Frees the memory
		// pointed to by the box pointer.
		//void RemoveBox(const q3Box* box);

		// Removes all boxes from this body and the broadphase.
		//void RemoveAllBoxes();

		inline void ApplyLinearForce(const Vector3& force) {
			_force = force;
		}
		inline void ApplyForceAtWorldPoint(const Vector3& force, const Point3& point) {

		}
		inline void ApplyTorque(const Vector3& torque) {
			_torque = torque;
		}
		inline bool IsAwake() const {
			//if( _flags == eAwake) {
			//    return true;
			//else 
			//    return false;

			return _flags & eAwake ? true : false;
		}
		inline float GetGravityScale() const {
			return _gravityScale;
		}
		inline void SetGravityScale(float scale) {
			_gravityScale = scale;
		}
		//void ApplyLinearImpulse(const Vector3& impulse);
		//void ApplyLinearImpulseAtWorldPoint(const Vector3& impulse, const Point3& point);
		//const Point3 GetLocalPoint(const Point3& p) const ;
		//const Vector3 GetLocalVector(const Vector3& v) const ;
		//const Vector3 GetWorldPoint(const Point3& p) const;
		//const Vector3 GetWorldVector(const Vector3& v) const;
		//const Vector3 GetVelocityAtWorldPoint(const Point3& p) const;

		inline const Vector3 GetLinearVelocity() const {
			return _linearVelocity;
		}
		inline void SetLinearVelocity(const Vector3& v) {
			if (_flags & eStatic)
				//assert(false);
				return;

			if (v.dot(v) > float(0.0))
			{
				SetToAwake();
			}

			_linearVelocity = v;
		}
		inline const Vector3 GetAngularVelocity() const {
			return _angularVelocity;
		}
		inline void SetAngularVelocity(const Vector3 v) {
			_angularVelocity = v;
		}
		//bool CanCollide(const Body *other) const;
		//const q3Transform GetTransform() const;
		int GetFlags() const {
			return _flags;
		}
		void SetLayers(int layers) {
			_layers = layers;
		}
		int GetLayers() const {
			return _layers;
		}
		//const q3Quaternion GetQuaternion() const;
		void* GetUserData() const {
			return _userData;
		}


		void SetToAwake();
		void SetToSleep();

		//void SetLinearDamping(float damping);
		//float GetLinearDamping(float damping) const;
		//void SetAngularDamping(float damping);
		//float GetAngularDamping(float damping) const;

		// Manipulating the transformation of a body manually will result in
		// non-physical behavior. Contacts are updated upon the next call to
		// q3Scene::Step( ). Parameters are in world space. All body types
		// can be updated.
		void SetTransform(const Vector3& position);
		void SetTransform(const Vector3& position, const Vector3& axis, float angle);

		// Used for debug rendering lines, triangles and basic lighting
		//void Render(q3Render* render) const;

		// Dump this rigid body and its shapes into a log file. The log can be
		// used as C++ code to re-create an initial scene setup.
		//void Dump(FILE* file, int index) const;

		inline float GetMass() const {
			return _mass;
		}
		//float GetInvMass() const;
	private:
		// _flags
		enum
		{
			eAwake = 0x001,
			eActive = 0x002,
			eAllowSleep = 0x004,
			eIsland = 0x010,
			eStatic = 0x020,
			eDynamic = 0x040,
			eKinematic = 0x080,
			eLockAxisX = 0x100,
			eLockAxisY = 0x200,
			eLockAxisZ = 0x400,
		};

		Matrix3 _invInertiaModel;
		Matrix3 _invInertiaWorld;
		float _mass;
		//float _invMass;
		Vector3 _linearVelocity;
		Vector3 _angularVelocity;
		Vector3 _force;
		Vector3 _torque;
		Matrix4 _tx;
		Vector4 _quaternion;
		Vector3 _localCenter;
		Vector3 _worldCenter;
		float _sleepTime;
		float _gravityScale;
		int _layers;
		int _flags;

		//q3Box* _boxes;
		void *_userData;
		q3Scene* _scene;
		Body* _next;
		Body* _prev;
		//int _islandIndex;

		float _linearDamping;
		float _angularDamping;

		//q3ContactEdge* _contactList;

		friend class q3Scene;
		//friend struct q3Manifold;
		//friend class q3ContactManager;
		//friend struct q3Island;
		//friend struct q3ContactSolver;

		Body(const DefaultBody& def, q3Scene* scene);

		void CalculateMassData();
		//void SynchronizeProxies();

	private:

	};

	struct DefaultBody {
		DefaultBody()
		{
				// Set all initial positions/velocties to zero
				axis.load();
				angle = float(0.0);
				position.load();
				linearVelocity.load();
				angularVelocity.load();

				// Usually a gravity scale of 1 is the best
				gravityScale = float(1.0);

				// Common default values
				bodyType = StaticBody;
				layers = 0x000000001;
				userData = NULL;
				allowSleep = true;
				awake = true;
				active = true;
				lockAxisX = false;
				lockAxisY = false;
				lockAxisZ = false;

				linearDamping = float(0.0);
				angularDamping = float(0.1);
			}

			Vector3 axis;			// Initial world transformation.
			float angle;				// Initial world transformation. Radians.
			Vector3 position;		// Initial world transformation.
			Vector3 linearVelocity;	// Initial linear velocity in world space.
			Vector3 angularVelocity;	// Initial angular velocity in world space.
			float gravityScale;		// Convenient scale values for gravity x, y and z directions.
			float layers;				// Bitmask of collision layers. Bodies matching at least one layer can collide.
			void* userData;			// Use to store application specific data.

			float linearDamping;
			float angularDamping;

			// Static, dynamic or kinematic. Dynamic bodies with zero mass are defaulted
			// to a mass of 1. Static bodies never move or integrate, and are very CPU
			// efficient. Static bodies have infinite mass. Kinematic bodies have
			// infinite mass, but *do* integrate and move around. Kinematic bodies do not
			// resolve any collisions.
			BodyType bodyType;

			bool allowSleep;	// Sleeping lets a body assume a non-moving state. Greatly reduces CPU usage.
			bool awake;			// Initial sleep state. True means awake.
			bool active;		// A body can start out inactive and just sits in memory.
			bool lockAxisX;		// Locked rotation on the x axis.
			bool lockAxisY;		// Locked rotation on the y axis.
			bool lockAxisZ;		// Locked rotation on the z axis.
		};
	};

