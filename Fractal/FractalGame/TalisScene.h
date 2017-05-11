#pragma once
#include <Fractal\include\scene\Scene.h>
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
	std::vector<fractal::fscene::GameObject*> objects;
	fractal::fscene::GameObject* dragon;
	fractal::fscene::GameObject* terrain;
	fractal::fscene::GameObject* skybox;
	fractal::fscene::FreeCamera* camera;
};

