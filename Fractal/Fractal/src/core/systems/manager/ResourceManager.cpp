#include "core\systems\manager\ResourceManager.h"
#include "core\resources\Resource.h"
#include "defines\deletemacros.h"

namespace fractal {
	namespace fcore {
		ResourceManager::ResourceManager()
			:Manager()
		{
		}

		ResourceManager::~ResourceManager()
		{
		}

		bool ResourceManager::initialize()
		{
			for (std::pair<const std::string, fresource::Resource*>& pair : this->m_resources)
			{
				if (!pair.second->initialize())
					return false;
			}

			return true;
		}

		bool ResourceManager::shutdown()
		{
			for (std::pair<const std::string, fresource::Resource*>& pair : this->m_resources)
			{
				if (!pair.second->shutdown())
					return false;

				SafeDelete(pair.second);
			}
			this->m_resources.clear();

			return true;
		}
	}
}