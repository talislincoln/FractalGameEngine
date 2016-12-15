#pragma once

#include "scene\Scene.h"
#include "scene\SceneObject.h"
<<<<<<< HEAD
#include "scene\objects\FreeCamera.h"

=======
#include <FractalPhysics\include\shapes\PhysicsBox.h>
>>>>>>> e68834e9c1dd03f1bf056453103d2977b69e5357
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
	fractal::fscene::SceneObject* cubeAttributes;
<<<<<<< HEAD
	//fractal::fscene::FreeCamera* camera;

=======
	fractal::fscene::SceneObject* cubeAttributes2;
	fractal::fscene::SceneObject* terrain;
	fractal::fphysics::PhysicsBox* box;
>>>>>>> e68834e9c1dd03f1bf056453103d2977b69e5357
	inline void testInput() {
		std::printf("input hit\n");
	}

	inline void testInput2() {
		std::printf("released\n");
	}
};

