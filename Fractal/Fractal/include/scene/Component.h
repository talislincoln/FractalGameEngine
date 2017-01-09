#ifndef _COMPONENT_H
#define _COMPONENT_H
#include <Fractal\include\scene\Object.h>

namespace fractal {
	namespace fscene {
		class GameObject;

		class Component : public Object
		{
		public:
			Component(const std::string& name = "");
			virtual ~Component();

			virtual bool initialize() = 0;
			virtual void update() = 0;
			virtual bool shutdown() = 0;

			void setOrderValue(int value);
			const int getOrderValue() const;

			void setParent(GameObject* parent);
			GameObject* getParent() const;

			static const int INVALID_ORDER_ID = -1;

		private:
			GameObject* m_parent;

			int m_orderId;
		};
	}
}

#endif // !_COMPONENT_H
