#include"core\systems\manager\SystemManager.h"

#include "core\systems\System.h"
#include "core\systems\manager\SystemFactory.h"
#include "interfaces\IDrawable.h"
#include "defines\deletemacros.h"

#ifndef _ALGORITHM
#include <algorithm>
#endif

namespace fractal {
	namespace fcore {
		SystemManager::SystemManager()
			:m_factory(nullptr)
		{
		}

		SystemManager::~SystemManager()
		{
		}

		System* SystemManager::getSystem(SystemType type)
		{
			//look for a position in the vector that satisfies the lambda function
			std::vector<System*>::const_iterator it = std::find_if(this->m_systems.begin(), this->m_systems.end(),
				[type](System* s) -> bool
			{
				return s->getType() == type;
			});

			//if the system was found, then just return the system
			if (it != this->m_systems.end())
				return (*it);

			//if there isn't a system of that type, then create one
			System* system = this->m_factory->createSystem(type);

			//cast the new created system to check if it is a drawable system
			if (dynamic_cast<IDrawable*>(system) != nullptr)
				this->m_drawableSystems.push_back(system);

			this->m_systems.push_back(system);

			return system;
		}

		std::vector<System*>& SystemManager::getDrawableSystems()
		{
			return this->m_drawableSystems;
		}

		std::vector<System*>& SystemManager::getSystems()
		{
			return this->m_systems;
		}

		bool SystemManager::initialize()
		{
			this->m_factory = new SystemFactory();

			return true;
		}

		bool SystemManager::shutdown()
		{
			SafeDelete(this->m_factory);

			bool result = true;
			for (System* system : this->m_systems)
			{
				if (!system->shutdown())
					result = false;

				SafeDelete(system);
			}

			//clear the space allocated for the systems array
			this->m_systems.clear();

			//all drawable systems have already been deleted because they're in the system vector as well
			this->m_drawableSystems.clear();

			return result;
		}
	}
}