#ifndef _SYSTEMFACTORY_H
#define _SYSTEMFACTORY_H

#include "defines\SystemType.h"

namespace fractal {
	namespace fcore {

		/// Forward declaration of System to prevent circular references
		class System;

		/** 
		
		*/
		class SystemFactory
		{
		public:
			SystemFactory();
			~SystemFactory();

			System* createSystem(SystemType type);
		};
	}
}

#endif // _SYSTEMFACTORY_H