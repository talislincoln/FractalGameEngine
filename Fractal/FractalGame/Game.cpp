#include "Game.h"

#include <Fractal\include\helpers\Singleton.h>
#include <Fractal\include\scene\SceneManager.h>
#include "MScene.h"


Game::Game()
{
}

Game::~Game()
{
}

bool Game::initialize() {
	fractal::fhelpers::Singleton<fractal::fscene::SceneManager>::getInstance().addScene(new MScene());
	//fractal::fhelpers::Singleton<fractal::fscene::SceneManager>::getInstance().addScene(new Scene2());

	fractal::fhelpers::Singleton<fractal::fscene::SceneManager>::getInstance().setActiveScene("MyScene");



	return true;
}

bool Game::shutdown() {
	return true;
}