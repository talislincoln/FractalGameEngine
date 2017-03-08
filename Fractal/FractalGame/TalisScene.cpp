#include "TalisScene.h"

#include <Fractal\include\graphics\Vertex.h>
#include <Fractal\include\helpers\Singleton.h>
#include <Fractal\include\scene\SceneManager.h>
#include <Fractal\include\core\systems\Input.h>
#include <Fractal\include\graphics\Mesh.h>
#include <Fractal\include\scene\components\MeshComponent.h>

#include <Fractal\include\scene\components\TerrainComponent.h>
#include <Fractal\include\scene\components\TransformComponent.h>
#include <Fractal\include\scene\components\PhysicsBodyComponent.h>
#include <Fractal\include\scene\components\PhysicsShapeComponent.h>

#include <FractalPhysics\include\shapes\PhysicsBox.h>
#include <Fractal\include\utils\LoadOBJ.h>
#include <Fractal\include\core\systems\manager\SystemManager.h>


TalisScene::TalisScene():
Scene("TalisScene"), test1(nullptr)
{
}


TalisScene::~TalisScene()
{
}

bool TalisScene::initialize() {
	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	test1 = new SceneObject("test1");
	camera = new FreeCamera("MainCamera");
	camera->setupInput(dynamic_cast<fcore::Input*>(fhelpers::Singleton<fcore::SystemManager>::getInstance().getSystem(SystemType::INPUT_SYSTEM)));
	test1->addComponent(new MeshComponent(LoadOBJ::load("cyl")));
	//camera->addComponent(new MeshComponent(LoadOBJ::load("cyl")));
	addGameObject(test1);
	addGameObject(camera);
	return Scene::initialize();
}

void TalisScene::update() {

	using namespace fractal;
	using namespace fscene;
	using namespace fmath;
	using namespace fgraphics;
	Scene::update();
}

bool TalisScene::shutdown() {
	return Scene::shutdown();
}