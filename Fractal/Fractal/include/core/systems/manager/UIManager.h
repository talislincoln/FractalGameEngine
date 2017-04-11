#ifndef UIMANAGER_H
#define UIMANAGER_H
#include "helpers\Manager.h"
#include "interfaces\IUserInterface.h"
#include <map>
namespace fractal {
	namespace fHUD {
		class UIComponent;
	}
	namespace fcore {
		class UIManager : public Manager {
		public:
			UIManager();
			virtual ~UIManager();
			virtual bool initialize();
			virtual bool shutdown();
			std::map<unsigned int, IUserInterface*>& getUIList();
			void addUiList(unsigned int depth, IUserInterface*);
		private:
			std::map<unsigned int, IUserInterface*> m_UIList;
		};
	}
}
#endif // !UIMANAGER_H
