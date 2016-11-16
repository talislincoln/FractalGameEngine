#include "MyScene.h"
#include "core\systems\Input.h"
#include "scene\ShapeComponent.h"
#include "graphics\Vertex.h"
#include "scene\components\MeshComponent.h"

MyScene::MyScene() :
	Scene("MyScene"), m_triangle(nullptr)
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

	this->m_triangle = new SceneObject("Triangle");

	std::vector<fmath::Point3> trianglePoints;
	trianglePoints.push_back(Point3(0.0f, 0.0f, 0.0f));
	trianglePoints.push_back(Point3(0.0f, 10.0f, 0.0f));
	trianglePoints.push_back(Point3(0.0f, 10.0f, 10.0f));
	PolygonShape* triangle = new PolygonShape(trianglePoints);
	triangle->setColor(Colour(1.0f, 1.0f, 0.0f,1.0f));

	//this->m_triangle->addComponent(new ShapeComponent(triangle));
	//addGameObject(m_triangle);


	std::vector<Vertex> vertices;
	//vertices.push_back(Vertex(Point3(0.5f, 0.5f, 0.0f)));
	vertices.push_back(Vertex(Point3(-0.5f, -0.5f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.5f, -0.5f, 0.0f)));
	vertices.push_back(Vertex(Point3(0.0f, 0.5f, 0.0f)));
	m_mesh = new SceneObject("MyMesh");
	m_mesh->addComponent(new MeshComponent(new Mesh(vertices)));

	addGameObject(m_mesh);

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
}