#ifndef _SINGLETON_H
#define _SINGLETON_H

#ifndef _ASSERT_H
#define _ASSERT_H
#include <assert.h>
#endif

#ifndef _DELETEMACROS_H
#include "defines\deletemacros.h"
#endif

namespace fractal {
	namespace fhelpers {
		template <typename T>
		class Singleton
		{
		public:
			static bool createInstance()
			{
				if (Singleton::m_instance != nullptr)
					return false;

				Singleton::m_instance = new T;
				return true;
			}

			static void destroyInstance()
			{
				SafeDelete(Singleton::m_instance);
			}

			static T& getInstance()
			{
				//check before returning a null pointer
				assert(Singleton::m_instance != nullptr);
				return *(Singleton::m_instance);
			}

			static bool hasInstance()
			{
				return m_instance != nullptr;
			}

		protected:
			Singleton() {}
			virtual ~Singleton() {}

		private:

			//Disable copy constructor & assignment operator
			Singleton(Singleton const&) {}
			Singleton& operator=(Singleton const&) {}

			static T* m_instance;
		};

		template<typename T>
		T * Singleton<T>::m_instance = nullptr;
	}
}
#endif // _SINGLETON_H

