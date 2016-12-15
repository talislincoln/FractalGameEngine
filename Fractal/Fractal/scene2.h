#pragma once

#include "scene\Scene.h"
#include "scene\SceneObject.h"
#include <FractalPhysics\include\shapes\PhysicsBox.h>
#include "scene\components\PhysicsShapeComponent.h"
#include "helpers\Singleton.h"
#include "core\systems\manager\SystemManager.h"

class Scene2 : public fractal::fscene::Scene
{
public:
	Scene2();
	virtual ~Scene2();

	virtual bool initialize();
	virtual void update();
	virtual bool shutdown();
	virtual void setupInput(fractal::fcore::Input* input);

private:
	fractal::fmath::Vector2 mousePos;
	fractal::fscene::SceneObject* cubeAttributes;
	fractal::fscene::SceneObject* cubeAttributes2;
	fractal::fscene::SceneObject* terrain;
	float direction;

	inline void testInput() {
		mousePos = input->getMousePosition();
		mousePos.x /= 400.0f;
		mousePos.y /= 300.0f;
		mousePos.x--;
		mousePos.y--;
		mousePos.y = -mousePos.y;
		printf("%f , %f   \n", mousePos.x, mousePos.y);
			fractal::fphysics::PhysicsBox* newBox = new fractal::fphysics::PhysicsBox(fractal::fmath::Vector3(0.5f));
			newBox->setLocalTransform(fractal::fmath::Vector3(mousePos.x, mousePos.y, 0.0f));
			cubeAttributes->addComponent(new fractal::fphysics::PhysicsShapeComponent(newBox));
			
	}

	inline void testInput2() {
		std::printf("released\n");
	}
};

