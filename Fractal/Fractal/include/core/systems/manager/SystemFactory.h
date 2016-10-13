#ifndef _SYSTEMFACTORY_H
#define _SYSTEMFACTORY_H

#ifndef _SYSTEMTYPE_H
#include "defines\SystemType.h"
#endif

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