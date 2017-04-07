 #ifndef _CAMERAMANAGER_H
#define _CAMERAMANAGER_H
#include <Fractal\include\helpers\Manager.h>

#include <vector>

namespace fractal {
	namespace fscene {
		class CameraComponent;
	}

	namespace fcore {
		class CameraManager : public Manager {
		public:
			CameraManager();
			virtual ~CameraManager();

			virtual bool initialize();
			virtual bool shutdown();

			void setActiveCamera(const std::string& name);
			void setActiveCamera(fscene::CameraComponent* camera);

			fscene::CameraComponent* getActiveCamera() const;

			void addCamera(fscene::CameraComponent* camera, bool setActive = true);

		private:
			std::vector<fscene::CameraComponent*> m_cameras;
			fscene::CameraComponent* m_activeCamera;
		};
	}
}

#endif // !_CAMERAMANAGER_H
