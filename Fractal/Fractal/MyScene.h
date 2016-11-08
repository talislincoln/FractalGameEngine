#pragma once

#include "scene\Scene.h"

class MyScene : public fractal::fscene::Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual bool initialize();
	virtual void update();
	virtual bool shutdown();

	virtual void setupInput(fractal::fcore::Input* input);

private:
	inline void testInput() {
		std::printf("input hit");
	}
};

