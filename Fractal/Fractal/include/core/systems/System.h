#ifndef _SYSTEM_H
#define _SYSTEM_H

#ifndef _SYSTEMTYPE_H
#include <Fractal\include\defines\SystemType.h>
#endif

/**
Base class to define a system.
*/

namespace fractal {
	namespace fcore {
		class System
		{
		public:
			/**
			Default constructor.
			\param type The type of the system being created.
			*/
			System(SystemType type);

			/**
			Default destructor.
			*/
			virtual ~System();

			/**
			Initialize the system.
			*/
			virtual bool initialize() = 0;
			
			/**
			Update method is called every loop iteration.
			*/
			virtual void update() = 0;
			
			/**
			Shutdown system.
			This method is called before the system is destroyed.
			*/
			virtual bool shutdown() = 0;

			/**
			Activate the system is called when the system is fully initialized and ready to be used.
			*/
			void activate();

			/**
			Deactivate system
			*/
			void deactivate();

			bool getIsActive() const;

			SystemType getType() const;

		private:
			SystemType m_systemType;
			bool m_isActive;
		};
	}
}



#endif // !_SYSTEM_H
