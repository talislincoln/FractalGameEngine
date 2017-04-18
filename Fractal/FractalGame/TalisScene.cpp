#include "TalisScene.h"

#include <Fractal\include\graphics\Vertex.h>
#include <Fractal\include\helpers\Singleton.h>
#include <Fractal\include\scene\SceneManager.h>
#include <Fractal\include\core\systems\Input.h>

#include <Fractal\include\scene\components\MeshComponent.h>
#include <Fractal\include\scene\components\TerrainComponent.h>
#include <Fractal\include\scene\components\TransformComponent.h>
#include <Fractal\include\scene\components\PhysicsBodyComponent.h>
#include <Fractal\include\scene\components\PhysicsShapeComponent.h>
#include "scene\components\UIButtonComponent.h"
#include <FractalPhysics\include\shapes\PhysicsBox.h>
#include <Fractal\include\utils\LoadOBJ.h>
#include <Fractal\include\core\systems\manager\SystemManager.h>

#include <Fractal\include\scene\components\SkyboxComponent.h>

#include "scene\components\UIComponent.h"

TalisScene::TalisScene():
Scene("TalisScene"), dragon(nullptr)
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

	dragon = new SceneObject("test1");
	dragon->addComponent(new MeshComponent(LoadOBJ::load("meshes/cyl")));
	dragon->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	dragon->addComponent(new fphysics::PhysicsShapeComponent(new fphysics::PhysicsBox()));
	dragon->getComponent<fphysics::PhysicsBodyComponent>()->SetAngularVelocity(Vector3(1.0f, 0.0f, 0.0f));
	dragon->getComponent<fphysics::PhysicsBodyComponent>()->SetGravityScale(0.0f);
	//dragon->addComponent(new fscene::CameraComponent());
	addGameObject(dragon);

	skybox = new SceneObject("skybox");
	skybox->addComponent(new SkyboxComponent());
	addGameObject(skybox);

	camera = new FreeCamera("MainCamera");
	camera->getTransform()->setPosition(fmath::Vector3(7.0f, 4.0f, 15.0f));
	addGameObject(camera);

	return Scene::initialize();
}

void TalisScene::update() {

	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	Scene::update();

	if (dragon->getComponent<fphysics::PhysicsBodyComponent>()->isGround()) {
		//test1->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(0, 10.0f, 0));
	}
}

bool TalisScene::shutdown() {
	return Scene::shutdown();
}

void TalisScene::setupInput(fractal::fcore::Input * input)
{
	camera->setupInput(input);
}
