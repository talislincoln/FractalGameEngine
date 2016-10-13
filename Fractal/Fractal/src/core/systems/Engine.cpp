#include "core\systems\Input.h"
#include "core\systems\Engine.h"
#include "core\systems\System.h"
#include "core\systems\Window.h"
#include "core\systems\manager\SystemManager.h"
#include "helpers\Singleton.h"

#include <iostream>

namespace fractal {
	namespace fcore {
		Engine::Engine() :
			m_isRunning(false)
		{
		}

		Engine::Engine(AbstractGame* game) :
			m_game(game), m_isRunning(false)
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

			m_isRunning = true;
			while (m_isRunning)
			{
				update();
				draw();
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
			if (!createManagers())
				return -1;

			using namespace fhelpers;

			//check for errors
			Window* window = dynamic_cast<Window*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::WINDOW_SYSTEM));
			if (window == nullptr)
				return 0; //error
			Input* input = dynamic_cast<Input*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::INPUT_SYSTEM));
			if (input == nullptr)
				return 0;
			/*MainTimer* timer = dynamic_cast<MainTimer*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::TIMER_SYSTEM));
			if (timer == nullptr)
				return FALSE;
			Graphics* graphics = dynamic_cast<Graphics*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::GRAPHICS_SYSTEM));
			if (graphics == nullptr)
				return FALSE;
			Logic* logic = dynamic_cast<Logic*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::LOGIC_SYSTEM));
			if (logic == nullptr)
				return FALSE;*/

			if (!window->initialize())
				return 0;// error
			if (!input->initialize())
				return 0;

			input->bindInput(new InputBinding(SDL_QUIT * 2, std::bind(&Engine::closeRequested, this), InputStateType::PRESSED));

			/*if (!timer->initialize())
				return FALSE;
			if (!graphics->initialize())
				return FALSE;

			logic->setGame(this->game);
			if (!logic->initialize())
				return FALSE;*/

			printf("input suceeded initializing");

			return 1; //true
		}

		void Engine::draw()
		{
			
			/*
			Graphics* graphics = dynamic_cast<Graphics*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::GRAPHICS_SYSTEM));
			graphics->beginDraw();

			for (System* system : fhelpers::Singleton<SystemManager>::getInstance().getDrawableSystems())
			{
				IDrawable* drawable_system = dynamic_cast<IDrawable*>(system);
				if (drawable_system->getCanDraw())
					drawable_system->draw();
			}

			graphics->endDraw();*/

			//the draw call should be within the beginDraw and endDraw function from the graphics system
			for (System* system : fhelpers::Singleton<SystemManager>::getInstance().getDrawableSystems())
			{
				IDrawable* drawable_system = dynamic_cast<IDrawable*>(system);
				if (drawable_system->getCanDraw())
					drawable_system->draw();
			}
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
			//Singleton<SceneManager>::createInstance();

			//if (!Singleton<WorldSettings>::getInstance().initialize())
			//	return false;
			if (!Singleton<SystemManager>::getInstance().initialize())
				return false;

			return true;
		}

		bool Engine::destroyManagers()
		{
			using namespace fhelpers;

			if (!Singleton<SystemManager>::getInstance().shutdown())
				return false;
			//if (!Singleton<WorldSettings>::getInstance().shutdown())
			//	return false;

			//Singleton<SceneManager>::destroyInstance();
			Singleton<SystemManager>::destroyInstance();
			//Singleton<WorldSettings>::destroyInstance();

			return true;
		}
	}
}
