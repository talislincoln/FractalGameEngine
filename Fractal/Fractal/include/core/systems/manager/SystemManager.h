#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "helpers\Manager.h"
#include "defines\SystemType.h"
#include "interfaces\IDrawable.h"

#ifndef _VECTOR
#include<vector>
#endif // !_VECTOR

/**
SystemManager is responsible to manager the created systems.
This class will handle the creation of each system whenever is required
*/

namespace fractal {
	namespace fcore {
		class System;
		class SystemFactory;

		class SystemManager : public Manager
		{
		public:
			SystemManager();
			virtual ~SystemManager();

			virtual bool initialize();
			virtual bool shutdown();

			System* getSystem(SystemType type);

			std::vector<System*>& getDrawableSystems();
			std::vector<System*>& getSystems();

		private:

			std::vector<System*> m_systems;
			std::vector<System*> m_drawableSystems;

			SystemFactory* m_factory;
		};
	}
}
#endif // !_SYSTEMMANAGER_H


