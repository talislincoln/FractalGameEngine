#ifndef _OBJECT_H
#define _OBJECT_H

#include <Fractal\include\helpers\ObjectCounter.h>

#include <string>

namespace fractal {
	namespace fscene {
		class Object : public fhelpers::ObjectCounter<Object>
		{
		public:
			Object(const std::string& name = "");
			virtual ~Object();

			virtual bool initialize() = 0;
			virtual bool shutdown() = 0;

			void setInitialized();
			const bool isInitialized() const;

			virtual void activate();
			virtual void deactive();
			const bool isActive() const;

			virtual void destroy();
			bool isDestroyed() const;

			void setName(const std::string& name);
			const std::string& getName() const;

		protected:
			template<typename T>
			const std::string generateName(const std::string& partialName)
			{
				return partialName + std::to_string(ObjectCounter<T>::getAmount());
			}

		private:
			bool m_isActive;

			bool m_isInitialized;
			bool m_isDestroyed;

			std::string name;
		};
	}
}

#endif // !_OBJECT_H
