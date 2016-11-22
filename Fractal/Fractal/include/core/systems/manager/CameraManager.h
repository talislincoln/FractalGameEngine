#ifndef _CAMERAMANAGER_H
#define _CAMERAMANAGer_H

#include "helpers\Manager.h"

#include <vector>

namespace fractal {
	class CameraObject;

	namespace fcore {
		class CameraManager : public Manager {
		public:
			CameraManager();
			virtual ~CameraManager();

			virtual bool initialize();
			virtual bool shutdown();

			void setActiveCamera(const std::string& name);
			void setActiveCamera(CameraObject* camera);

			CameraObject* getActiveCamera() const;

			void addCamera(CameraObject* camera, bool setActive = true);

		private:
			std::vector<CameraObject*> m_cameras;
			CameraObject* m_activeCamera;
		};
	}
}

#endif // !_CAMERAMANAGER_H
