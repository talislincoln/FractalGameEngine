#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <Fractal\include\helpers\Manager.h>
#include <Fractal\include\helpers\Singleton.h>
#include <Fractal\include\interfaces\IDrawable.h>

#include <Fractal\include\core\systems\manager\CameraManager.h>

#include <string>

#ifndef _VECTOR
#include <vector>
#endif // !_VECTOR


namespace fractal
{
	using namespace fcore;
	namespace fscene {
		class Scene;

		class SceneManager : public Manager, public IDrawable
		{
		public:
			SceneManager();
			virtual ~SceneManager();

			virtual bool initialize();
			void update();
			virtual void draw();
			virtual bool shutdown();

			void addScene(Scene* scene);

			void setActiveScene(const std::string& name);
			Scene* getActiveScene() const;

		private:
			template<typename T>
			void setupManager()
			{
				using namespace fhelpers;
				using namespace fcore;
				if (Singleton<T>::hasInstance())
				{
					//Singleton<Logger>::getInstance().log(_T("Check if we can keep data that will be used in a different scene aswell, so not all data need to be unloaded."), LOGTYPE_TODO);
					Singleton<T>::getInstance().shutdown();
				}
				else Singleton<T>::createInstance();

				Singleton<T>::getInstance().initialize();
			}
			template<typename T>
			void destroyManager()
			{
				using namespace fhelpers;
				using namespace fcore;
				Singleton<T>::getInstance().shutdown();
				Singleton<T>::destroyInstance();
			}

			Scene* m_activeScene;
			std::vector<Scene*> m_scenes;
		};
	}
}

#endif // !_SCENEMANAGER_H
