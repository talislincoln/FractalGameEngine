#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "helpers\Manager.h"
#include "defines\SystemType.h"
#include "interfaces\IDrawable.h"

#ifndef _VECTOR
#include<vector>
#endif // !_VECTOR

/**
SystemManager is responsible to manager all systems in the engine as Singletons.
This class will handle the creation of each system whenever is required. It is also responsible of
removing all the created system from the memory when necessary.
@see SystemType
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

			/**
			Gets the system of the specific <code>type</code>.
			This function will look for a system of the specific type and return it.
			It will create a system of that specific type if it is the first time being called.
			@see SystemType
			@param type one of the possible types of system.
			@return the system of the specified type.
			*/
			System* getSystem(SystemType type);

			/**
			Get all the drawable systems.
			A drawable system as all systems that inherit from the interface <code>IDrawable</code>.
			@see IDrawable
			@return All systems that implements that interface
			*/
			std::vector<System*>& getDrawableSystems();

			/**
			Get all systems.
			Return all systems that were already created.
			@return All systems being managed
			*/
			std::vector<System*>& getSystems();

		private:

			///Vector that holds all the created systems
			std::vector<System*> m_systems;
			///Holds a point to the systems that implements the IDrawable interface
			std::vector<System*> m_drawableSystems;

			SystemFactory* m_factory;
		};
	}
}
#endif // !_SYSTEMMANAGER_H


