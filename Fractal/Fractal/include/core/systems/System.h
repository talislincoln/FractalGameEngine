#ifndef _SYSTEM_H
#define _SYSTEM_H

#ifndef _SYSTEMTYPE_H
#include "defines\SystemType.h"
#endif

namespace fractal {
	namespace fcore {
		class System
		{
		public:
			System(SystemType type);
			virtual ~System();

			virtual bool initialize() = 0;
			virtual void update() = 0;
			virtual bool shutdown() = 0;

			void activate();
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
