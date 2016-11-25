#include "MyScene.h"
#include "core\systems\Input.h"
#include "graphics\Vertex.h"
#include "scene\components\MeshComponent.h"

MyScene::MyScene() :
	Scene("MyScene"), m_mesh(nullptr), m_mesh2(nullptr)
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

	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, 0.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, 0.5f, 0.0f)));
	m_mesh = new SceneObject("MyMesh");

	std::vector<Vertex> vertices2;
	vertices2.push_back(Vertex(Point3(0.0f, 0.5f, 0.0f)));
	vertices2.push_back(Vertex(Point3(0.5f, 0.5f, 0.0f)));
	vertices2.push_back(Vertex(Point3(0.5f, 0.0f, 0.0f)));
	m_mesh2 = new SceneObject("MyMesh2");

	m_mesh->addComponent(new MeshComponent(new Mesh(vertices)));
	m_mesh2->addComponent(new MeshComponent(new Mesh(vertices2)));

	addGameObject(m_mesh);
	addGameObject(m_mesh2);

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