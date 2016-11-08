#include "MyScene.h"
#include "core\systems\Input.h"


MyScene::MyScene() :
	Scene("MyScene")
{
}


MyScene::~MyScene()
{
}

bool MyScene::initialize() {
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