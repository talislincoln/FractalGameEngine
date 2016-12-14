#include "core\systems\manager\SystemFactory.h"
#include "core\systems\Window.h"
#include "core\systems\Input.h"
#include "core\systems\Logic.h"
#include "core\systems\Graphics.h"
#include "core\systems\PhysicsWorld.h"
namespace fractal {
	namespace fcore {
		SystemFactory::SystemFactory()
		{
		}
		SystemFactory::~SystemFactory()
		{
		}

		System* SystemFactory::createSystem(SystemType type)
		{
			switch (type)
			{
				case SystemType::WINDOW_SYSTEM: return new Window();
				case SystemType::INPUT_SYSTEM: return new Input();
				case SystemType::LOGIC_SYSTEM: return new Logic();
				case SystemType::GRAPHICS_SYSTEM: return new Graphics();
				case SystemType::PHYSICS_SYSTEM: return new fphysics::PhysicsWorld();
			//case SystemType::TIMER_SYSTEM: return new MainTimer();
			}

			return nullptr;
		}

	}
}