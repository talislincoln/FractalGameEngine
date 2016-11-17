#ifndef _OBJECTCOUNTER_H
#define _OBJECTCOUNTER_H

namespace fractal {
	namespace fhelpers {
		template <typename T>
		class ObjectCounter
		{
		public:
			ObjectCounter()
			{
				++objectAmount;
			}

			virtual ~ObjectCounter()
			{
				--objectAmount;
			}

			static unsigned long getAmount() { return objectAmount; }

		private:
			static unsigned long objectAmount;
		};

		template<typename T>
		unsigned long ObjectCounter<T>::objectAmount = 0;
	}
}


#endif