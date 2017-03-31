#include "scene\components\TerrainComponent.h"
#include "helpers\Singleton.h"
#include "core\systems\PhysicsWorld.h"
#include "core\systems\manager\SystemManager.h"
namespace fractal {
	namespace fscene {

		TerrainComponent::TerrainComponent( const std::string& name, const fgraphics::Material* m, float height) :
			Component(name == "" ? "TerrainComponent" : name),m_TerrainMaterial(m), m_normal(fmath::Vector3::UP){
			this->height = height;
		}
		TerrainComponent::~TerrainComponent() {

		}

		void TerrainComponent::update()
		{
		}
		bool TerrainComponent::initialize() {

			static_cast<fphysics::PhysicsWorld*>(fhelpers::Singleton<fcore::SystemManager>::getInstance().getSystem(SystemType::PHYSICS_SYSTEM))->setTerrainComponent(this);
			return true;
		}
		bool TerrainComponent::shutdown()
		{
			return false;
		}
		void TerrainComponent::draw()
		{
		}
	}
}