#ifndef _ENGINE_H
#define _ENGINE_H

namespace fractal {
	namespace fcore {
		class AbstractGame;

		class Engine
		{
		public:
			Engine(AbstractGame* game);
			~Engine();

			int run();

		private:

			int initialize();
			void draw();
			void update();
			int shutDown();

			bool createManagers();
			bool destroyManagers();

			inline void closeRequested() { m_isRunning = false; }

			bool m_isRunning;
			AbstractGame* m_game;
		};

	}
}

#endif // _ENGINE_H
