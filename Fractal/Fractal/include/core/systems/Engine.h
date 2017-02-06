#ifndef _ENGINE_H
#define _ENGINE_H

/**
The main instance of the Fractal Game engine
*/
namespace fractal {
	namespace fcore {
		class AbstractGame;

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

			float m_maxFPS;

			AbstractGame* m_game; ///< Instance of the game running in the engine
		};
	}
}

#endif // _ENGINE_H
