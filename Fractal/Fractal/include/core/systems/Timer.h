#ifndef _TIMER_H
#define _TIMER_H

#include <Fractal\include\core\systems\System.h>

#ifndef _VECTOR_
#include <vector>
#endif

namespace fractal {

	namespace fscene{
		class TimerObject;
	}

	namespace fcore {
		class Timer : public System {
		public:
			Timer();
			virtual ~Timer();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			fscene::TimerObject* getWorldTimer() const;

			void addTimer(fscene::TimerObject* timer);
			fscene::TimerObject* getTimer(const std::string& name) const;

			static float m_deltaTime;

		private:
			fscene::TimerObject* m_worldTimer;
			std::vector<fscene::TimerObject*> m_timerObjects;
		};
	}
}



#endif // !_TIMER_H
