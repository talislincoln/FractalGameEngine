#ifndef _PHYSICS_WORLD_H
#define _PHYSICS_WORLD_H
#include <vector>
#include "core\systems\System.h"
#include "scene\Component.h"
#include <FractalPhysics\include\shapes\PhysicsShape.h>
#include <FractalPhysics\include\PhysicsMath.h>
namespace fractal {
	namespace fcore {

		class PhysicsWorld : public System
		{
		public:
			PhysicsWorld(const float gravity = float(9.8));
			virtual ~PhysicsWorld();

			std::vector<fscene::Component> colliderList;
			std::vector<fscene::Component> bodyList;

		};
	}
}

#endif // !_PHYSICS_WORLD_H