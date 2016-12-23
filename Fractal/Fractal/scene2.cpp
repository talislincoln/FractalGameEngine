#include "Scene2.h"
#include "core\systems\Input.h"
#include "graphics\Vertex.h"
#include "scene\components\MeshComponent.h"
#include "scene\components\PhysicsBodyComponent.h"
#include "scene\components\PhysicsShapeComponent.h"
#include "scene\components\TransformComponent.h"
#include "scene\components\TerrainComponent.h"
Scene2::Scene2() :
	Scene("Scene2"), cubeAttributes(nullptr), direction(1.0)//, indices(nullptr)
{
}

Scene2::~Scene2()
{
}

bool Scene2::initialize() {
	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	using namespace fcore;
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


	terrain = new SceneObject("terrain");

	addGameObject(cubeAttributes);
	//;w; 

	cubeAttributes->addComponent(new TransformComponent());
	cubeAttributes->addComponent(new MeshComponent(new Mesh(vertices)));
	cubeAttributes->addComponent(new fphysics::PhysicsBodyComponent(new fphysics::PhysicsBody()));
	cubeAttributes->addComponent(new fphysics::PhysicsShapeComponent(new fphysics::PhysicsBox(fmath::Vector3(0.5f))));
	//;w; 
	terrain->addComponent(new TerrainComponent());

	addGameObject(terrain);
	//Quaternion q;
	cubeAttributes->getComponent<TransformComponent>()->setScale(Vector3(0.5f, 0.5f, 0.5f));
	cubeAttributes->getComponent<TransformComponent>()->setPosition(Vector3(0.0f, 0.0f, -0.5f));

	//cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(-1.0f, 0.0f, 0.0f));
	cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->SetAngularVelocity(Vector3(3.0f, 3.0f, 0.0f));
	return Scene::initialize();
}

void Scene2::update() {
	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	Scene::update();
	if (cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->isGround()) {
		//cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(0.0f, 4.0f, 0.0f));
	}
	if (!cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->IsAwake()) {
		cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->SetLinearVelocity(Vector3(0, 3.0f , direction));
		direction *= -1;
	}
	//cubeAttributes->getComponent<fphysics::PhysicsBodyComponent>()->ApplyLinearForce(Vector3(0.0f, 9.8f, 0.0f)); // even out gravity. so we can do some testing.
	//cubeAttributes2->getComponent<fphysics::PhysicsBodyComponent>()->ApplyLinearForce(Vector3(0.0f, 9.8f, 0.0f)); // even out gravity. so we can do some testing.


}

bool Scene2::shutdown() {
	return Scene::shutdown();
}

void Scene2::setupInput(fractal::fcore::Input* input) {
	input->bindInput(fractal::fcore::InputBinding(SDL_BUTTON_LEFT, std::bind(&Scene2::testInput, this), fractal::InputStateType::MOUSE_CLICK));
}