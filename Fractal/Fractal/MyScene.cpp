#include "MyScene.h"
#include "core\systems\Input.h"
#include "graphics\Vertex.h"
#include "scene\components\MeshComponent.h"
#include "scene\components\TransformComponent.h"

#include <FractalMath\Vector.h>

MyScene::MyScene() :
	Scene("MyScene"), 
	camera(nullptr),
	cubeAttributes(nullptr)//, indices(nullptr)
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

	this->camera = new FreeCamera("Main Camera");
	camera->getTransform()->setPosition(Vector3(0));
	
	//addGameObject(this->camera);


	//;w; setting the points and other attributes
	std::vector<Vertex> vertices;
	//;w; side 1
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
	//;w; side 2 OPPOSITE
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
	//;w; side 3 OPPOSITE
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
	//;w; side 5 OPPOSITE
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
<<<<<<< HEAD
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
	cubeAttributes->addComponent(new MeshComponent(new Mesh(vertices)));
	addGameObject(cubeAttributes);
=======
	////;w; side 2
	//vertices.push_back(Vertex(Point3(-0.5f, -0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, 0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, -0.5f, 0.5f)));
	////;w; side 3
	//vertices.push_back(Vertex(Point3(-0.5f, 0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, 0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5)));
	//vertices.push_back(Vertex(Point3(-0.5f, 0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, 0.5f, 0.5f)));
	////;w; side 4
	//vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, 0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, -0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, -0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	////;w; side 5
	//vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, -0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, -0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, -0.5f, -0.5f)));
	////;w; side 6
	//vertices.push_back(Vertex(Point3(-0.5f, 0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, 0.5f, -0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, 0.5f, 0.5f)));
	//vertices.push_back(Vertex(Point3(-0.5f, 0.5f, -0.5f)));
	//cubeAttributes = new SceneObject("cubeAttributes");
	//;w; 
	//cubeAttributes->addComponent(new MeshComponent(new Mesh(vertices)));
	camera->addComponent(new MeshComponent(new Mesh(vertices)));
	//;w; 
	//addGameObject(cubeAttributes);
	addGameObject(this->camera);
>>>>>>> cf713e4a3c30344503d29a0d1a72dd9547f90b71

	return Scene::initialize();
}

void MyScene::update() {
	Scene::update();
}

bool MyScene::shutdown() {
	return Scene::shutdown();
}

void MyScene::setupInput(fractal::fcore::Input* input) {
	camera->setupInput(input);
}