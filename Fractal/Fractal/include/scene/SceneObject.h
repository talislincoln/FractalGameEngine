#ifndef _SCENEOBJECT_H
#define _SCENEOBJECT_H

#include "GameObject.h"
#include "interfaces\IDrawable.h"

namespace fractal {
	namespace fscene {
		class TransformComponent;

		class SceneObject : public GameObject, public IDrawable
		{
		public:
			SceneObject(const std::string& name = "");
			virtual ~SceneObject();

			virtual bool initialize();
			virtual void update();
			virtual void draw();
			virtual bool shutdown();

			TransformComponent* getTransform() const;

		private:
			TransformComponent* m_transform;
		};
	}
}
#endif // !_SCENEOBJECT_H
