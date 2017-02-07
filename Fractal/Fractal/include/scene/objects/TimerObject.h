#ifndef _TIMEROBJECT_H
#define _TIMEROBJECT_H

#include <Fractal\include\scene\Object.h>
#include <SDL\SDL.h>

namespace fractal {
	namespace fscene {
		class TimerObject : public fractal::fscene::Object {
		public:
			TimerObject(const std::string& name);
			virtual ~TimerObject();

			virtual bool initialize();
			void update();
			virtual bool shutdown();

			float getTotalTime() const;	

			inline float getDeltaTime() const {
				return static_cast<float>(m_deltaTime);
			}

			void reset();

		private:
			void start();
			void stop();

			bool m_stopped;

			Uint64 m_baseTime;
			Uint64 m_pauseTime;
			Uint64 m_stopTime;
			Uint64 m_previousTime;
			Uint64 m_currentTime;

			double m_secondsPerCount;
			double m_deltaTime;
		};
	}
}

#endif // !_TIMEROBJECT_H
