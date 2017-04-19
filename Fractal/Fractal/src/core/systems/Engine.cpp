#include "core\systems\Input.h"
#include "core\systems\Engine.h"
#include "core\systems\System.h"
#include "core\systems\Window.h"
#include "core\systems\Logic.h"
#include "core\systems\Graphics.h"
#include "core\systems\Timer.h"
#include "core\systems\HUD.h"
#include "core\systems\PhysicsWorld.h"

#include "core\systems\manager\SystemManager.h"
#include "scene\SceneManager.h"

#include "helpers\Singleton.h"

#include <iostream>

namespace fractal {
	namespace fcore {

		Engine::Engine(AbstractGame* game) :
			m_game(game), m_isRunning(false),
			m_maxFPS(60.0f)
		{
		}

		Engine::~Engine()
		{
		}

		int Engine::run()
		{
			if (!initialize())
			{
				printf("Engine failed to init.");
				//Singleton<Logger>::getInstance().log(_T("Initialization of the engine failed."), LOGTYPE_ERROR);
				//return INITIALIZATION_FAILED;
				return -1;
			}

			// Seed the random number generator
			// this will set the the random numbers to be always random (in theory?)
			srand(SDL_GetTicks());

			m_isRunning = true;
			while (m_isRunning)
			{
				static_cast<Timer*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::TIMER_SYSTEM))->startFPS();
				update();
				draw();
				//printf("fps: %f\n", static_cast<Timer*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::TIMER_SYSTEM))->endFPS());

				//create the fixed timestep
			}

			if (!shutDown())
			{
				//Singleton<Logger>::getInstance().log(_T("Shutdown of the engine failed."), LOGTYPE_ERROR);
				//return SHUTDOWN_FAILED;

				printf("failed to shutdown");
				return -2;
			}

			return 0;
		}

		int Engine::initialize()
		{
			//Init the managers (Scene and System manager)
			if (!createManagers())
				return -1;

			using namespace fhelpers;

			//Create instances for the different types of system
			//and check if the system is null after creation
			Logic* logic = static_cast<Logic*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::LOGIC_SYSTEM));
			if (logic == nullptr)
				return 0;
			Window* window = static_cast<Window*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::WINDOW_SYSTEM));
			if (window == nullptr)
				return 0; //error
			Input* input = static_cast<Input*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::INPUT_SYSTEM));
			if (input == nullptr)
				return 0;
			Graphics* graphics = static_cast<Graphics*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::GRAPHICS_SYSTEM));
			if (graphics == nullptr)
				return 0;
			Timer* timer = static_cast<Timer*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::TIMER_SYSTEM));
			if (timer == nullptr)
				return 0;

			fphysics::PhysicsWorld* physics = static_cast<fphysics::PhysicsWorld*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::PHYSICS_SYSTEM));
			if (physics == nullptr)
				return 0;
			//HUDs system need to be after Graphics system
			HUD* HUDs = static_cast<HUD*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::HUD_SYSTEM));
			if (HUDs == nullptr)
				return 0;
			
			if (!physics->initialize())
				return 0;
			if (!window->initialize())
				return 0;
			if (!graphics->initialize())
				return 0;
			if (!HUDs->initialize())
				return 0;

			input->bindInput(InputBinding(SDL_QUIT * 2, std::bind(&Engine::closeRequested, this), InputStateType::PRESSED));

			if (!timer->initialize())
				return 0;

			logic->setGame(this->m_game);
			if (!logic->initialize())
				return 0;

			if (!input->initialize())
				return 0;

			printf("input succeeded initializing");

			return 1; //true
		}

		void Engine::draw()
		{
			Graphics* graphics = static_cast<Graphics*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::GRAPHICS_SYSTEM));
			graphics->beginDraw();

			for (IDrawable* system : fhelpers::Singleton<SystemManager>::getInstance().getDrawableSystems())
			{
				if (system->getCanDraw())
					system->draw();
			}

			graphics->endDraw();
		}

		void Engine::update()
		{
			for (System* system : fhelpers::Singleton<SystemManager>::getInstance().getSystems())
				system->update();
		}

		int Engine::shutDown()
		{
			if (!destroyManagers())
				return -1;

			return 1;
		}

		bool Engine::createManagers()
		{
			using namespace fhelpers;

			//Singleton<WorldSettings>::createInstance(); //this holds the informations to configure the engine/game
			Singleton<SystemManager>::createInstance();
			Singleton<fscene::SceneManager>::createInstance();

			//if (!Singleton<WorldSettings>::getInstance().initialize())
			//	return false;
			if (!Singleton<SystemManager>::getInstance().initialize())
				return false;
			//scene manager is initialized in the Logic class

			return true;
		}

		bool Engine::destroyManagers()
		{
			using namespace fhelpers;
			using namespace fscene;

			if (!Singleton<SystemManager>::getInstance().shutdown())
				return false;
			// scene manager is shut down in the Logic class
			//if (!Singleton<WorldSettings>::getInstance().shutdown())
			//	return false;

			Singleton<SystemManager>::destroyInstance();
			Singleton<SceneManager>::destroyInstance();
			//Singleton<WorldSettings>::destroyInstance();

			return true;
		}
	}
}
