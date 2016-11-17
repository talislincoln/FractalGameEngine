#pragma once

#include "core\game\AbstractGame.h"

class MyGame : public fractal::fcore::AbstractGame
{
public:
	MyGame();
	virtual ~MyGame();

	virtual bool initialize();
	virtual bool shutdown();
};

