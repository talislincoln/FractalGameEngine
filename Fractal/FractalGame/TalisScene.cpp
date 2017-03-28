#include "TalisScene.h"

#include <Fractal\include\graphics\Vertex.h>
#include <Fractal\include\helpers\Singleton.h>
#include <Fractal\include\scene\SceneManager.h>
#include <Fractal\include\core\systems\Input.h>
#include <Fractal\include\graphics\Mesh.h>
#include <Fractal\include\scene\components\MeshComponent.h>

#include <Fractal\include\scene\components\TerrainComponent.h>
#include <Fractal\include\scene\components\TransformComponent.h>
#include <Fractal\include\scene\components\PhysicsBodyComponent.h>
#include <Fractal\include\scene\components\PhysicsShapeComponent.h>

#include <FractalPhysics\include\shapes\PhysicsBox.h>
#include <Fractal\include\utils\LoadOBJ.h>
#include <Fractal\include\core\systems\manager\SystemManager.h>


TalisScene::TalisScene():
Scene("TalisScene"), test1(nullptr)
{
}


TalisScene::~TalisScene()
{
}

bool TalisScene::initialize() {
	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	terrain = new SceneObject("terrain");

	terrain->addComponent(new TerrainComponent());

	addGameObject(terrain);
	test1 = new SceneObject("test1");
	test1->addComponent(new MeshComponent(LoadOBJ::load("meshes/cyl")));
	test1->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	test1->getComponent<fphysics::PhysicsBodyComponent>()->SetAngularVelocity(Vector3(1.0f, 0.0f, 0.0f));
	test1->getComponent<fphysics::PhysicsBodyComponent>()->SetGravityScale(0.0f);
	camera = new FreeCamera("MainCamera");
	//camera->addComponent(new MeshComponent(LoadOBJ::load("cyl")));
	addGameObject(test1);
	addGameObject(camera);
	return Scene::initialize();
}

void TalisScene::update() {

	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	Scene::update();
}

bool TalisScene::shutdown() {
	return Scene::shutdown();
}

void TalisScene::setupInput(fractal::fcore::Input * input)
{
	camera->setupInput(input);
}
