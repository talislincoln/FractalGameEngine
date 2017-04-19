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
	MeshData* md = LoadOBJ::load("meshes/wall_e");
	fgraphics::Vao* box = new Vao();
	box->loadMeshIntoOpenGL(md);
	Material* mat = new DefaultMaterial();
	mat->loadNewTexture((Texture::newTexture("images/wall_e").anisotropic().create()));
	mat->loadNewTexture((Texture::newTexture("images/wall_e").anisotropic().create()), 1);

	for (unsigned int i = 0; i < 10; i++) {
		objects.push_back(new SceneObject());
		objects[i]->addComponent(new MeshComponent(mat, box));
		addGameObject(objects[i]);
		objects[i]->getTransform()->setPosition(Vector3(rand() % 25 - 12, rand() % 25 - 10, rand() % 25 - 12));
		objects[i]->getTransform()->setScale(Vector3(rand() % 100 / 1000.0f));
	}
	terrain = new SceneObject("terrain");
	terrain->addComponent(new TerrainComponent());
	addGameObject(terrain);

	objects[0]->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	objects[0]->addComponent(new fphysics::PhysicsShapeComponent(new fphysics::PhysicsBox()));
	objects[0]->getComponent<fphysics::PhysicsBodyComponent>()->SetAngularVelocity(Vector3(0.0f, 1.0f, 0.0f));

	dragon = new SceneObject("test1");
	addGameObject(dragon);
	dragon->addComponent(new MeshComponent(LoadOBJ::load("meshes/dragon")));
	dragon->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	dragon->addComponent(new fphysics::PhysicsShapeComponent(new fphysics::PhysicsBox()));
	dragon->getComponent<fphysics::PhysicsBodyComponent>()->SetAngularVelocity(Vector3(0.0f, 1.0f, 0.0f));
	dragon->getComponent<fphysics::PhysicsBodyComponent>()->SetGravityScale(0.0f);
	//dragon->addComponent(new fscene::CameraComponent());

	skybox = new SceneObject("skybox");
	skybox->addComponent(new SkyboxComponent());
	addGameObject(skybox);

	camera = new FreeCamera("MainCamera");
	camera->getTransform()->setPosition(fmath::Vector3(0.0f, 0.0f, 0.0f));
	addGameObject(camera);

	return Scene::initialize();
}

void TalisScene::update() {

	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	Scene::update();

	if (objects[0]->getComponent<fphysics::PhysicsBodyComponent>()->isGround()) {
		objects[0]->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(0, 10.0f, 0));
	}
}

bool TalisScene::shutdown() {
	return Scene::shutdown();
}

void TalisScene::setupInput(fractal::fcore::Input * input)
{
	camera->setupInput(input);
}
