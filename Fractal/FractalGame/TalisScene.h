#pragma once
#include <Fractal\include\scene\Scene.h>
#include <Fractal\include\scene\SceneObject.h>
class TalisScene : public fractal::fscene::Scene
{
public:
	TalisScene();
	virtual ~TalisScene();

	virtual bool initialize();
	virtual void update();
	virtual bool shutdown();

};

