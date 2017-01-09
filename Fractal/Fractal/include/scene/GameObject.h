#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include "Object.h"
#include <Fractal\include\core\systems\Input.h>

namespace fractal {
	namespace fscene {
		class Component;
		class Scene;

		class GameObject : public Object//, public IInput
		{
		public:
			GameObject(const std::string& name = "");
			virtual ~GameObject();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			void setScene(Scene* scene);
			Scene* getScene() const;
			void setParent(GameObject* parent);
			GameObject* getParent() const;

			std::vector<GameObject*> getChildren() const;

			template <typename T> T* getComponent() const;
			std::vector<Component*> getComponents() const;

			void addComponent(Component* component);
			void removeComponent(Component* component);

			void addChild(GameObject* object);
			void removeChild(GameObject* object);

		private:
			std::vector<GameObject*> m_children;
			std::vector<Component*> m_components;

			GameObject* m_parent;

			Scene* m_currentScene;
		};

		template <typename T>
		T* GameObject::getComponent() const
		{
			for (Component* c : this->m_components)
			{
				T* new_c = dynamic_cast<T*>(c);
				if (new_c == nullptr)
					continue;

				return new_c;
			}

			return nullptr;
		}
	}
}
#endif // !_GAMEOBJECT_H
