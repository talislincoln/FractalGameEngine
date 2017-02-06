#ifndef _TIMEROBJECT_H
#define _TIMEROBJECT_H

#include <Fractal\include\scene\Object.h>

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
				return m_deltaTime;
			}

			void reset();

		private:
			void start();
			void stop();

			bool m_stopped;

			float m_baseTime;
			float m_pauseTime;
			float m_stopTime;
			float m_previousTime;
			float m_currentTime;

			float m_deltaTime;

			const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
			const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
			const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
		};
	}
}

#endif // !_TIMEROBJECT_H
