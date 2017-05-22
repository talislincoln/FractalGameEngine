#include "MScene.h"

#include <Fractal\include\graphics\Vertex.h>
#include <Fractal\include\helpers\Singleton.h>
#include <Fractal\include\scene\SceneManager.h>
#include <Fractal\include\core\systems\Input.h>
#include <Fractal\include\scene\components\MeshComponent.h>

#include <Fractal\include\scene\components\TerrainComponent.h>
#include <Fractal\include\scene\components\TransformComponent.h>
#include <Fractal\include\scene\components\PhysicsBodyComponent.h>
#include <Fractal\include\scene\components\PhysicsShapeComponent.h>
#include <Fractal\include\utils\LoadOBJ.h>
#include <FractalPhysics\include\shapes\PhysicsBox.h>

MScene::MScene() :
	Scene("MyScene"),
	//camera(nullptr),
	cubeAttributes(nullptr)
{
}

MScene::~MScene()
{
}

bool MScene::initialize() {
	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;

	//this->camera = new FreeCamera("Main Camera");
	//camera->getTransform()->setPosition(Vector3(0));
	//;w; setting the points and other attributes and in clock-wise order
	std::vector<Point3> vertices;

	vertices.push_back( (Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back( (Point3(0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back( (Point3(0.5f, 0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back( (Point3(0.5f, 0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back( (Point3(-0.5f, 0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back( (Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 0.0f)));
	//;w; side 2
	vertices.push_back( (Point3(-0.5f, -0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back( (Point3(-0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back( (Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back( (Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back( (Point3(0.5f, -0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back( (Point3(-0.5f, -0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 0.0f)));
	//;w; side 3
	vertices.push_back( (Point3(-0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back( (Point3(-0.5f, -0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back( (Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back( (Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back( (Point3(-0.5f, 0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back( (Point3(-0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	//;w; side 4
	vertices.push_back( (Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back( (Point3(0.5f, 0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back( (Point3(0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back( (Point3(0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back( (Point3(0.5f, -0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back( (Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	//;w; side 5
	vertices.push_back( (Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back( (Point3(-0.5f, -0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back( (Point3(0.5f, -0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back( (Point3(0.5f, -0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back( (Point3(0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back( (Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));
	//;w; side 6 
	vertices.push_back( (Point3(-0.5f, 0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back( (Point3(0.5f, 0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back( (Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back( (Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back( (Point3(-0.5f, 0.5f, 0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back( (Point3(-0.5f, 0.5f, -0.5f)));
	vertices.push_back( (Point3(0.0f, 0.0f, 1.0f)));

	cubeAttributes = new GameObject("cubeAttributes");

	cubeAttributes2 = new GameObject("cubeAttributes2");

	terrain = new GameObject("terrain");
	//;w; 
	cubeAttributes2->addComponent(new TransformComponent());
	cubeAttributes2->addComponent(new MeshComponent(LoadOBJ::load("test")));
	cubeAttributes2->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	cubeAttributes2->addComponent(new fphysics::PhysicsShapeComponent(new fphysics::PhysicsBox(fmath::Vector3(0.5f))));

	cubeAttributes->addComponent(new TransformComponent());
	cubeAttributes->addComponent(new MeshComponent(LoadOBJ::load("test")));
	cubeAttributes->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	cubeAttributes->addComponent(new fphysics::PhysicsShapeComponent(new fphysics::PhysicsBox(fmath::Vector3(0.5f))));
	//;w; 
	terrain->addComponent(new TerrainComponent());

	addGameObject(terrain);
	addGameObject(cubeAttributes);
	addGameObject(cubeAttributes2);
	//Quaternion q;
	cubeAttributes->getComponent<TransformComponent>()->setScale(Vector3(0.5f, 0.5f, 0.5f));
	cubeAttributes->getComponent<TransformComponent>()->setPosition(Vector3(1.0f, 0.0f, 0.5f));
	cubeAttributes2->getComponent<TransformComponent>()->setScale(Vector3(0.5f, 0.5f, 0.5f));
	cubeAttributes2->getComponent<TransformComponent>()->setPosition(Vector3(-1.0f, 1.5f, 0.5f));
	cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(-1.0f, 1.0f, 0.0f));
	cubeAttributes2->getComponent<fphysics::PhysicsBodyComponent>()->SetAngularVelocity(Vector3(-1.0f, 0.0f, 0.0f));
	cubeAttributes2->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(1.0f, 5.0f, 0.0f));

	/*camera->addComponent(new MeshComponent(new Mesh(vertices)));
	addGameObject(this->camera);*/

	return Scene::initialize();
}

void MScene::update() {

	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	Scene::update();
	if (!cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->IsAwake()) {

		fractal::fhelpers::Singleton<fractal::fscene::SceneManager>::getInstance().setActiveScene("Scene2");
	}

	//cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->ApplyLinearForce(Vector3(0.0f, 9.8f, 0.0f)); // even out gravity. so we can do some testing.
	//cubeAttributes2->getComponent<fphysics::PhysicsBodyComponent>()->ApplyLinearForce(Vector3(0.0f, 9.8f, 0.0f)); // even out gravity. so we can do some testing.


}

bool MScene::shutdown() {
	return Scene::shutdown();
}

void MScene::setupInput(fractal::fcore::Input* input) {
	printf("hello there");
	//	camera->setupInput(input);
}