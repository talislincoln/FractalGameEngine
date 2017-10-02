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
	//MeshData* md = LoadOBJ::load("meshes/barrel");
	MeshData* md = LoadOBJ::load("meshes/barrel"); //;w; loads an obj file
	fgraphics::Vao* box = new Vao(); //;w; creates a new vao
	box->loadMeshIntoOpenGL(md); //;w; ??? vao attaches to the model object
	Material* mat = new DefaultMaterial(); //;w; sets material as default
	//;w; test with outline
	mat->loadNewTexture((Texture::newTexture("images/barrel").anisotropic().create())); //;w; loads file for diffuse
	//mat->loadNewTexture((Texture::newTexture("images/barrel").anisotropic().create()), 1); //;w; loads file for specular
	
	MeshData* md2 = LoadOBJ::load("meshes/dragon"); //;w; loads an obj file
	fgraphics::Vao* dragonVao = new Vao(); //;w; creates a new vao
	dragonVao->loadMeshIntoOpenGL(md2); //;w; ??? vao attaches to the model object
	Material* mat2 = new DefaultMaterial(); //;w; sets material as default

	MeshData* walle = LoadOBJ::load("meshes/wall_e"); //;w; loads an obj file
	fgraphics::Vao* walleVao = new Vao(); //;w; creates a new vao
	walleVao->loadMeshIntoOpenGL(walle); //;w; ??? vao attaches to the model object
	Material* mat3 = new DefaultMaterial(); //;w; sets material as default
	mat3->loadNewTexture((Texture::newTexture("images/wall_e").anisotropic().create())); //;w; loads file for diffuse
	mat3->loadNewTexture((Texture::newTexture("images/wall_e").anisotropic().create()), 1); //;w; loads file for specular

	for (unsigned int i = 0; i < 10; i++) { //;w; renders the model object multiple times
		objects.push_back(new GameObject());
		objects[i]->addComponent(new MeshComponent(mat, box));
		addGameObject(objects[i]);
		objects[i]->getTransform()->setPosition(Vector3(rand() % 25 - 12.0f, rand() % 25 - 10.0f, rand() % 25 - 12.0f));
		//objects[i]->getTransform()->setScale(Vector3(rand() % 100 / 1000.0f));
	}
	for (unsigned int i = 10; i < 20; i++) { //;w; renders the model object multiple times
		objects.push_back(new GameObject());
		objects[i]->addComponent(new MeshComponent(mat2, dragonVao));
		addGameObject(objects[i]);
		objects[i]->getTransform()->setPosition(Vector3(rand() % 25 - 12.0f, rand() % 25 - 10.0f, rand() % 25 - 12.0f));
		objects[i]->getTransform()->setScale(Vector3(0.5f));
	}

	for (unsigned int i = 20; i < 30; i++) { //;w; renders the model object multiple times
		objects.push_back(new GameObject());
		objects[i]->addComponent(new MeshComponent(mat3, walleVao));
		addGameObject(objects[i]);
		objects[i]->getTransform()->setPosition(Vector3(rand() % 25 - 12.0f, rand() % 25 - 10.0f, rand() % 25 - 12.0f));
		objects[i]->getTransform()->setScale(Vector3(0.1f));
	}
	terrain = new GameObject("terrain");
	terrain->addComponent(new TerrainComponent());
	addGameObject(terrain);

	objects[0]->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	objects[0]->addComponent(new fphysics::PhysicsShapeComponent(new fphysics::PhysicsBox()));
	objects[0]->getComponent<fphysics::PhysicsBodyComponent>()->SetAngularVelocity(Vector3(0.0f, 1.0f, 0.0f));

	dragon = new GameObject("test1");
	addGameObject(dragon);
	dragon->addComponent(new MeshComponent(LoadOBJ::load("meshes/cyl")));
	dragon->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	dragon->addComponent(new fphysics::PhysicsShapeComponent(new fphysics::PhysicsBox()));
	dragon->getComponent<fphysics::PhysicsBodyComponent>()->SetAngularVelocity(Vector3(0.0f, 1.0f, 0.0f));
	dragon->getComponent<fphysics::PhysicsBodyComponent>()->SetGravityScale(0.0f);
	//dragon->addComponent(new fscene::CameraComponent());

	skybox = new GameObject("skybox"); //;w; loads cubemap
	skybox->addComponent(new SkyboxComponent());
	addGameObject(skybox);

	camera = new FreeCamera("MainCamera", 0.2f); //;w; loads camera to the scene
	camera->getTransform()->setPosition(fmath::Vector3(0.0f, 0.0f, 0.0f));
	addGameObject(camera);

	return Scene::initialize();
}

void TalisScene::update() {

	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	Scene::update(); //;w; update the scene

	if (objects[0]->getComponent<fphysics::PhysicsBodyComponent>()->isGround()) {
		objects[0]->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(0, 10.0f, 0));
	}
}

bool TalisScene::shutdown() {
	return Scene::shutdown();
}

void TalisScene::setupInput(fractal::fcore::Input * input)
{
	camera->setupInput(input); //;w; checks for camera input
}
