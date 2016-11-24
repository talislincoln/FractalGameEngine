 #ifndef _CAMERAMANAGER_H
#define _CAMERAMANAGER_H

#include "helpers\Manager.h"

#include <vector>

namespace fractal {
	namespace fscene {
		class CameraObject;
	}

	namespace fcore {
		class CameraManager : public Manager {
		public:
			CameraManager();
			virtual ~CameraManager();

			virtual bool initialize();
			virtual bool shutdown();

			void setActiveCamera(const std::string& name);
			void setActiveCamera(fscene::CameraObject* camera);

			fscene::CameraObject* getActiveCamera() const;

			void addCamera(fscene::CameraObject* camera, bool setActive = true);

		private:
			std::vector<fscene::CameraObject*> m_cameras;
			fscene::CameraObject* m_activeCamera;
		};
	}
}

#endif // !_CAMERAMANAGER_H
