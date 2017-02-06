#include "core\systems\Input.h"
#include "core\systems\Engine.h"
#include "core\systems\System.h"
#include "core\systems\Window.h"
#include "core\systems\Logic.h"
#include "core\systems\Graphics.h"
#include "core\systems\Timer.h"

#include "core\systems\manager\SystemManager.h"
#include "scene\SceneManager.h"

#include "helpers\Singleton.h"

#include <iostream>

namespace fractal {
	namespace fcore {

		Engine::Engine(AbstractGame* game) :
			m_game(game), m_isRunning(false),
			m_maxFPS(60.f)
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
			//srand(GetTickCount());

			//if using message system:
			//MSG msg = {};
			/*while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				update();
				draw();
			}
			*/

			//subscribe a function to the event to close the window
			//this function will assignt the is running to false
			//and close the application at the end of it

			Uint32 start32, now32;
			Uint64 start, now;

			start32 = SDL_GetTicks();
			start = SDL_GetPerformanceCounter();
			SDL_Delay(1000);
			now = SDL_GetPerformanceCounter();
			now32 = SDL_GetTicks();
			SDL_Log("Delay 1 second = %d ms in ticks, %f ms according to performance counter", (now32 - start32), (double)((now - start) * 1000) / SDL_GetPerformanceFrequency());

			m_isRunning = true;
			while (m_isRunning)
			{
				update();
				draw();

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
			Window* window = dynamic_cast<Window*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::WINDOW_SYSTEM));
			if (window == nullptr)
				return 0; //error
			Input* input = dynamic_cast<Input*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::INPUT_SYSTEM));
			if (input == nullptr)
				return 0;
			Logic* logic = dynamic_cast<Logic*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::LOGIC_SYSTEM));
			if (logic == nullptr)
				return 0;
			Graphics* graphics = dynamic_cast<Graphics*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::GRAPHICS_SYSTEM));
			if (graphics == nullptr)
				return 0;
			Timer* timer = dynamic_cast<Timer*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::TIMER_SYSTEM));
			if (timer == nullptr)
				return 0;
			

			if (!window->initialize())
				return 0;
			if (!input->initialize())
				return 0;
			if (!graphics->initialize())
				return 0;


			input->bindInput(InputBinding(SDL_QUIT * 2, std::bind(&Engine::closeRequested, this), InputStateType::PRESSED));

			if (!timer->initialize())
				return 0;

			logic->setGame(this->m_game);
			if (!logic->initialize())
				return 0;

			printf("input succeeded initializing");

			return 1; //true
		}

		void Engine::draw()
		{
			Graphics* graphics = dynamic_cast<Graphics*>(fhelpers::Singleton<SystemManager>::getInstance().getSystem(SystemType::GRAPHICS_SYSTEM));
			graphics->beginDraw();

			for (System* system : fhelpers::Singleton<SystemManager>::getInstance().getDrawableSystems())
			{
				IDrawable* drawable_system = dynamic_cast<IDrawable*>(system);
				if (drawable_system->getCanDraw())
					drawable_system->draw();
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
