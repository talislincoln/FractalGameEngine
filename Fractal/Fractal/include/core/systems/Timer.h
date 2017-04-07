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
			virtual bool fixedUpdate();
			virtual bool shutdown();

			inline fscene::TimerObject* getWorldTimer() const {
				return m_worldTimer;
			}

			void addTimer(fscene::TimerObject* timer);

			fscene::TimerObject* getTimer(const std::string& name) const;

			inline float getDeltaTime() {
				return deltaTime;
			}

		private:
			static float deltaTime;
			fscene::TimerObject* m_worldTimer;
			std::vector<fscene::TimerObject*> m_timerObjects;
		};
	}
}



#endif // !_TIMER_H
