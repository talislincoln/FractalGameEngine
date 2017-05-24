#include "core\resources\Resource.h"

namespace fractal {
	namespace fcore {
		namespace fresource {
			Resource::Resource(const std::string& resourcePath, ResourceType type)
				:m_resourcePath(resourcePath)
				, m_resourceType(type)
			{
				int start_index = this->m_resourcePath.find_last_of('\\');
				if (start_index == std::string::npos)
					start_index = this->m_resourcePath.find_last_of('/');
				++start_index;
				int end_index = this->m_resourcePath.find_last_of('.');

				this->m_resourceName = this->m_resourcePath.substr(start_index, end_index - start_index);
			}

			Resource::~Resource()
			{
			}

			const std::string& Resource::getResourcePath()
			{
				return this->m_resourcePath;
			}
			
			const std::string& Resource::getResourceName()
			{
				return this->m_resourceName;
			}

			ResourceType Resource::getResourceType()
			{
				return this->m_resourceType;
			}
		}
	}
}