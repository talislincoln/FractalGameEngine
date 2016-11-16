#pragma once

#include "scene\Scene.h"
#include "scene\SceneObject.h"
#include "scene\PolygonShape.h"

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
	fractal::fscene::SceneObject* m_triangle;
	fractal::fscene::SceneObject* m_mesh;

	inline void testInput() {
		std::printf("input hit");
	}
};

