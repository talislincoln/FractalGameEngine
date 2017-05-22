#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include "Object.h"
#include <Fractal\include\core\systems\Input.h>
#include <Fractal\include\interfaces\IDrawable.h>
#include <Fractal\include\scene\components\TransformComponent.h>

namespace fractal {
	namespace fscene {
		class Component;
		class Scene;

		class GameObject : public Object, public IDrawable//, public IInput
		{
		public:
			GameObject(const std::string& name = "");
			virtual ~GameObject();

			virtual bool initialize();
			virtual void update();
			virtual void draw() const;
			virtual void fixedUpdate();
			virtual bool shutdown();

			void setScene(Scene* scene);
			Scene* getScene() const;
			void setParent(GameObject* parent);
			GameObject* getParent() const;
			const GameObject* getRootParent() const;
			std::vector<GameObject*> getChildren() const;

			template <typename T> T* getComponent() const;
			std::vector<Component*> getComponents() const;

			TransformComponent* GameObject::getTransform() const;

			void addComponent(Component* component);
			void removeComponent(Component* component);

			void addChild(GameObject* object);
			void removeChild(GameObject* object);

			unsigned int getDepth() const;
		private:
			unsigned int m_depth;
			std::vector<GameObject*> m_children;
			std::vector<Component*> m_components;

			GameObject* m_parent;

			TransformComponent* m_transformComponent;

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
