#ifndef _PHYSICS_WORLD_H
#define _PHYSICS_WORLD_H
#include <Fractal\include\core\systems\System.h>
#include <Fractal\include\defines\SystemType.h>
namespace fractal {

	class PhysicsWorld : public fcore::System
	{
	public:
		PhysicsWorld();
			//System(fcore::SystemType::PHYSICS_SYSTEM) 
		virtual ~PhysicsWorld();
	};

}

#endif // !_PHYSICS_WORLD_H