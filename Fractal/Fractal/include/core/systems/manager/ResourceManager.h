#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include <Fractal\include\helpers\Manager.h>
#include <Fractal\include\core\resources\Resource.h>

#ifndef _MAP_
#include <map>
#endif
#ifndef _ALGORITHM_
#include <algorithm>
#endif

namespace fractal {
	namespace fcore {
		class ResourceManager : public Manager
		{
		public:
			ResourceManager();
			virtual ~ResourceManager();

			virtual bool initialize();
			virtual bool shutdown();

			template<typename T> T* getResource(const std::string& path);

		private:

			std::map<const std::string, fresource::Resource*> m_resources;
		};

		template<typename T>
		T* ResourceManager::getResource(const std::string& path)
		{
			if (this->m_resources[path] != nullptr)
				return dynamic_cast<T*>(this->m_resources[path]);

			T * newResource = new T(path);
			newResource->initialize();

			this->m_resources[path] = newResource;

			return newResource;
		}
	}
}


#endif // !_RESOURCEMANAGER_H
