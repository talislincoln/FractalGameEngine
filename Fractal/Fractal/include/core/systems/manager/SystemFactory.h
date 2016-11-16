#ifndef _SYSTEMFACTORY_H
#define _SYSTEMFACTORY_H

#include "defines\SystemType.h"

namespace fractal {
	namespace fcore {

		/// Forward declaration of System to prevent circular references
		class System;

		/** 
		Class responsible to create the possible systems for the engine.
		*/
		class SystemFactory
		{
		public:
			SystemFactory();
			~SystemFactory();

			///Returns a new System based on the specified type
			System* createSystem(SystemType type);
		};
	}
}

#endif // _SYSTEMFACTORY_H