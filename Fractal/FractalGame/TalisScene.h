#pragma once
#include <Fractal\include\scene\Scene.h>
#include <Fractal\include\scene\SceneObject.h>
#include <Fractal\include\scene\objects\FreeCamera.h>
class TalisScene : public fractal::fscene::Scene
{
public:
	TalisScene();
	virtual ~TalisScene();

	virtual bool initialize();
	virtual void update();
	virtual bool shutdown();

	virtual void setupInput(fractal::fcore::Input* input);

private:
	fractal::fscene::SceneObject* test1;
	fractal::fscene::GameObject* test2;
	fractal::fscene::SceneObject* terrain;
	fractal::fscene::FreeCamera* camera;
};

