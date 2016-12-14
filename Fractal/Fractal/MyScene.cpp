#include "MyScene.h"
#include "core\systems\Input.h"
#include "graphics\Vertex.h"
#include "helpers\Singleton.h"
#include "scene\SceneManager.h"
#include "scene\components\MeshComponent.h"
#include "scene\components\PhysicsBodyComponent.h"
#include "scene\components\PhysicsShapeComponent.h"
#include "scene\components\TransformComponent.h"
#include <FractalPhysics\include\shapes\PhysicsBox.h>
#include "scene\components\TerrainComponent.h"
MyScene::MyScene() :
	Scene("MyScene"), cubeAttributes(nullptr)//, indices(nullptr)
{
}

MyScene::~MyScene()
{
}

bool MyScene::initialize() {
	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	//;w; setting the points and other attributes
	std::vector<Vertex> vertices;

	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, 0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 0.0f)));
	//;w; side 2
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 0.0f)));
	//;w; side 3
	vertices.push_back(Vertex(Point3(-0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, 0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	//;w; side 4
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	//;w; side 5
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));
	//;w; side 6 
	vertices.push_back(Vertex(Point3(-0.5f, 0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 1.0f)));
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, 0.5f, 0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 0.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, 0.5f, -0.5f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.0f, 1.0f)));

	cubeAttributes = new SceneObject("cubeAttributes");

	cubeAttributes2 = new SceneObject("cubeAttributes2");

	terrain = new SceneObject("terrain");
	//;w; 
	cubeAttributes2->addComponent(new TransformComponent());
	cubeAttributes2->addComponent(new MeshComponent(new Mesh(vertices)));
	cubeAttributes2->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	cubeAttributes2->addComponent(new fphysics::PhysicsShapeComponent(new fphysics::PhysicsBox(fmath::Vector3(0.5f))));

	cubeAttributes->addComponent(new TransformComponent());
	cubeAttributes->addComponent(new MeshComponent(new Mesh(vertices)));
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
	cubeAttributes2->getComponent<TransformComponent>()->setPosition(Vector3(-1.0f, 0.5f, 0.5f));
	cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(-1.0f, 0.0f, 0.0f));
	cubeAttributes2->getComponent<fphysics::PhysicsBodyComponent>()->SetAngularVelocity(Vector3(-1.0f, 0.0f, 0.0f));
	cubeAttributes2->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(1.0f, 0.0f, 0.0f));

	return Scene::initialize();
}

void MyScene::update() {

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

bool MyScene::shutdown() {
	return Scene::shutdown();
}

void MyScene::setupInput(fractal::fcore::Input* input) {
	input->bindInput(fractal::fcore::InputBinding('a', std::bind(&MyScene::testInput, this), fractal::InputStateType::PRESSED));
	input->bindInput(fractal::fcore::InputBinding('a', std::bind(&MyScene::testInput2, this), fractal::InputStateType::RELEASED));
}