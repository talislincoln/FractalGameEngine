#include "Game.h"

#include <Fractal\include\helpers\Singleton.h>
#include <Fractal\include\scene\SceneManager.h>
#include "MScene.h"
#include "TalisScene.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::initialize() {
	fractal::fhelpers::Singleton<fractal::fscene::SceneManager>::getInstance().addScene(new TalisScene());
	//fractal::fhelpers::Singleton<fractal::fscene::SceneManager>::getInstance().addScene(new Scene2());

	fractal::fhelpers::Singleton<fractal::fscene::SceneManager>::getInstance().setActiveScene("TalisScene");



	return true;
}

bool Game::shutdown() {
	return true;
}