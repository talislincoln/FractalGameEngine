#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H
#include "scene\Component.h"
#include "interfaces\IUserInterface.h"
#include "graphics\materials\DefaultUIMaterial.h"
#include "graphics\Vao.h"
namespace fractal {
	namespace fHUD {
		class UIComponent : public fscene::Component, public IUserInterface {
		public:
			UIComponent(fgraphics::Material* m = new fgraphics::DefaultUIMaterial());
			~UIComponent();
			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();
			virtual void draw2D();
		protected:
			fgraphics::Material* m_material;
			fgraphics::Vao* m_vao;
			fmath::Vector2 m_offset; // from center, value between -1, 1
			float m_rolation; // in degrees;
			fmath::Vector2 m_scale;// from center, value between 0, 1
		};
	}
}
#endif // !UI_COMPONENT_H
