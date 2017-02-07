#ifndef _PHYSICS_WORLD_H
#define _PHYSICS_WORLD_H
#include <vector>
#include <FractalMath\Quaternion.h>
#include <Fractal\include\core\systems\System.h>
#include <Fractal\include\scene\Component.h>

#include <FractalPhysics\include\shapes\PhysicsShape.h>
#include <FractalPhysics\include\PhysicsMath.h>
#include <Fractal\include\scene\GameObject.h>

namespace fractal {
	namespace fscene{
		class TerrainComponent;
	}
	namespace fphysics {
#ifndef SLEEP_LINEAR
#define SLEEP_LINEAR float( 0.01 )
#endif // !SLEEP_LINEAR
#ifndef SLEEP_ANGULAR
#define SLEEP_ANGULAR float ( 3.0 / 180) * F_PI;
#endif // !SLEEP_ANGULAR
#ifndef SLEEP_TIME
#define SLEEP_TIME float(0.5)
#endif // !SLEEP_TIME

//#define BAUMGARTE r32( 0.2 )

//#define PENETRATION_SLOP r32( 0.05 )

		struct VelocityState
		{
			fmath::Vector3 w;
			fmath::Vector3 v;
		};

		class PhysicsWorld : public fcore::System
		{
		public:
			PhysicsWorld(const fmath::Vector3 gravity = fmath::Vector3(0, -9.8f, 0));
			virtual ~PhysicsWorld() {

			}
			void update();
			void destroy();

			bool initialize();
			bool shutdown();

			void simulation();
			bool checkCollision();

			void reaction(fscene::GameObject* a, fscene::GameObject* b);
			void setTerrainComponent(fscene::TerrainComponent* terrain);
			bool m_allowSleep;
			bool m_enableFriction;
			fmath::Vector3 m_gravity;
			float dtime; //temp
			bool collided; //temp
			VelocityState *m_velocities;
			std::vector<fscene::GameObject*> gameOjbectWithBodyList;
		private:
			fscene::TerrainComponent* terrain;

		};
	}
}

#endif // !_PHYSICS_WORLD_H