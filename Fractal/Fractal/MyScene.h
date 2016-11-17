#pragma once

#include "scene\Scene.h"
#include "scene\SceneObject.h"

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
	fractal::fscene::SceneObject* m_mesh;
	fractal::fscene::SceneObject* m_mesh2;

	inline void testInput() {
		std::printf("input hit\n");
	}

	inline void testInput2() {
		std::printf("released\n");
	}
};

