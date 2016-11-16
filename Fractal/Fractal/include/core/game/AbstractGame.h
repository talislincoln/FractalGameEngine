#ifndef _ABSTRACTGAME_H
#define _ABSTRACTGAME_H

/**
Abstract interface to define a game.
*/

namespace fractal {
	namespace fcore {
		class AbstractGame
		{
		public:
			AbstractGame();
			virtual ~AbstractGame();

			virtual bool initialize() = 0;
			virtual bool shutdown() = 0;
		};
	}
}

#endif