#ifndef _SCENE_H
#define _SCENE_H

#include "Object.h"
#include "GameObject.h"
#include <Fractal\include\interfaces\IDrawable.h>
#include <Fractal\include\core\systems\Input.h>

#include <vector>

namespace fractal {
	namespace fcore {
		class Renderer;
		class CameraManager;
	}
	namespace fscene {
		class Scene : public Object, public IDrawable//, public IInput
		{
		public:
			Scene(const std::string& name);
			virtual ~Scene();

			virtual bool initialize();
			virtual void update();
			virtual void draw() const;
			virtual bool shutdown();

			virtual void setupInput(fcore::Input* input);

			virtual void activate();
			virtual void deactive();

			virtual void destroy();

			void addGameObject(GameObject* object);
			void removeGameObject(GameObject* object);

			//void setRenderer(Renderer* renderer);
			//Renderer* getRenderer() const;
			//void setCameraManager(fcore::CameraManager* manager);
			//fcore::CameraManager* getCameraManager() const;
			// i dont see the need of this when are are using singleton to search for manager

			fcore::Input* input;
		private:
			//Renderer* renderer;
			//fcore::CameraManager* m_cameraManager;
			std::vector<GameObject*> m_objects;
		};
	}
}

#endif // !_SCENE_H
