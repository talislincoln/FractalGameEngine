#ifndef _GAME_H
#include <Fractal\include\core\game\AbstractGame.h>

class Game : public fractal::fcore::AbstractGame
{
public:
	Game();
	virtual ~Game();

	virtual bool initialize();
	virtual bool shutdown();
};
#endif // !_GAME_H


