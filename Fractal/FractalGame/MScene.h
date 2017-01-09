#ifndef _MSCENE_H

#include <Fractal\include\scene\Scene.h>
#include <Fractal\include\scene\SceneObject.h>
#include <Fractal\include\core\systems\Input.h>

class MScene : public fractal::fscene::Scene
{
public:
	MScene();
	virtual ~MScene();

	virtual bool initialize();
	virtual void update();
	virtual bool shutdown();

	virtual void setupInput(fractal::fcore::Input* input);

private:
	fractal::fscene::SceneObject* cubeAttributes;
	fractal::fscene::SceneObject* cubeAttributes2;
	fractal::fscene::SceneObject* terrain;
	//fractal::fphysics::PhysicsBox* box;
	inline void testInput() {
		std::printf("input hit\n");
	}

	inline void testInput2() {
		std::printf("released\n");
	}
};
#endif // !_MSCENE_H



