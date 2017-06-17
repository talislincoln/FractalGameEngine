#ifndef _RESOURCE_H
#define _RESOURCE_H

#include <string>
#include <GL\glew.h>
#include "defines\ResourceType.h"

namespace fractal {
	namespace fcore {
		namespace fresource {
			class Resource
			{
			public:
				Resource(const std::string& resourcePath, ResourceType type);
				virtual ~Resource();

				virtual bool initialize() = 0;
				virtual bool shutdown() = 0;

				const std::string& getResourcePath();
				const std::string& getResourceName();

				ResourceType getResourceType();

				inline const int getId() const {
					return m_id;
				}

			private:
				std::string m_resourcePath;
				std::string m_resourceName;

				ResourceType m_resourceType;

			protected:
				GLuint m_id;
			};
		}
	}
}

#endif // !_RESOURCE_H
