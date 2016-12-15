#include "scene\components\TerrainComponent.h"
#include "helpers\Singleton.h"
#include "core\systems\PhysicsWorld.h"
#include "core\systems\manager\SystemManager.h"
namespace fractal {
	namespace fscene {

		TerrainComponent::TerrainComponent(float height, const std::string& name) :
			Component(name == "" ? "TerrainComponent" : name) , normal(0.0f,1.0f,0.0f) {
			this->height = height;
		}
		TerrainComponent::~TerrainComponent() {

		}
		bool TerrainComponent::initialize() {

			dynamic_cast<fphysics::PhysicsWorld*>(fhelpers::Singleton<fcore::SystemManager>::getInstance().getSystem(SystemType::PHYSICS_SYSTEM))->setTerrainComponent(this);
			return true;
		}
	}
}