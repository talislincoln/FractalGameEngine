#include "MyScene.h"
#include "core\systems\Input.h"
#include "graphics\Vertex.h"
#include "scene\components\MeshComponent.h"

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

	return Scene::initialize();
}

void MyScene::update() {
	Scene::update();
}

bool MyScene::shutdown() {
	return Scene::shutdown();
}

void MyScene::setupInput(fractal::fcore::Input* input) {
	input->bindInput(fractal::fcore::InputBinding('a', std::bind(&MyScene::testInput, this), fractal::InputStateType::PRESSED));
	input->bindInput(fractal::fcore::InputBinding('a', std::bind(&MyScene::testInput2, this), fractal::InputStateType::RELEASED));
}