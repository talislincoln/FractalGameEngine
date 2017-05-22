#ifndef _ENGINE_H
#define _ENGINE_H

#include "core\systems\System.h"
#include "core\systems\manager\SystemManager.h"

#include "scene\SceneManager.h"
#include "defines\SystemType.h"
#include "helpers\Singleton.h"

#include "core\systems\Input.h"
#include "core\systems\Window.h"
#include "core\systems\Logic.h"
#include "core\systems\Graphics.h"
#include "core\systems\Timer.h"
#include "core\systems\HUD.h"
#include "core\systems\PhysicsWorld.h"
/**
The main instance of the Fractal Game engine
*/
namespace fractal {
	namespace fcore {
		class AbstractGame;

#define LOGIC_SYSTEM static_cast<Logic*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::LOGIC_SYSTEM))
#define WINDOW_SYSTEM static_cast<Window*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::WINDOW_SYSTEM))
#define INPUT_SYSTEM static_cast<Input*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::INPUT_SYSTEM))
#define GRAPHICS_SYSTEM static_cast<Graphics*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::GRAPHICS_SYSTEM))
#define TIMER_SYSTEM static_cast<Timer*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::TIMER_SYSTEM))
#define PHYSICS_SYSTEM static_cast<fphysics::PhysicsWorld*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::PHYSICS_SYSTEM))
#define HUD_SYSTEM static_cast<HUD*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::HUD_SYSTEM))

		class Engine
		{
		public:
			/**
			Constructor that creates the engine with a specific game.
			@see AbstractGame
			*/
			Engine(AbstractGame* game);
			~Engine();

			///Starts the engine
			int run();

		private:

			int initialize();
			void draw();
			void update();
			int shutDown();

			bool createManagers();
			bool destroyManagers();

			/**
			Callback method to stop the engine when the 'X' button on the window is pressed.
			*/
			inline void closeRequested() { m_isRunning = false; }

			bool m_isRunning; ///< boolean that defines if the engine should break the infinit loop

			float m_maxFPS; ///< Max/desired engine frames per second

			AbstractGame* m_game; ///< Instance of the game running in the engine
		};
	}
}

#endif // _ENGINE_H
