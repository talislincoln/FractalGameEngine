#ifndef _SYSTEMFACTORY_H
#define _SYSTEMFACTORY_H

#include "defines\SystemType.h"
/**
Class responsible to create the possible systems for the engine.
This class is not supposed to be called by iteself. The system manager has a instance of this class,
and before using this to create a new system, it checks if the system already exists.
@see SystemManager
*/
namespace fractal {
	namespace fcore {

		/// Forward declaration of the class System to prevent circular references
		class System;

		
		class SystemFactory
		{
		public:
			///Default Constructor
			SystemFactory();
			///Default Destructor
			~SystemFactory();

			/**
			Creates and returns a system of a specific type.
			This function doesn't check if the system was previously created,
			thus doesn't prevent memory leak. It should be called within the SystemManager class.
			@see SystemManager
			@see SystemType
			@param type the type of the system to be created
			@return The new system created
			*/
			System* createSystem(SystemType type);
		};
	}
}

#endif // _SYSTEMFACTORY_H