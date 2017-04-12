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

			void AnchorCenter(bool x, bool y);
			void AnchorLeft();
			void AnchorRight();
			void AnchorTop();
			void AnchorBottom();

			void setOffset(const fmath::Vector2& v);
			void setScale(const fmath::Vector2& s);
			void setRolate(float r);
			void setTranform(const fmath::Vector2& v, float r, const fmath::Vector2& s);
			void makeDirty();

		protected:

			fmath::Vector2 m_offset, m_scale;
			float m_rolation;
			fmath::Matrix4 m_UITranform;
			fgraphics::Material* m_material;
			fgraphics::Vao* m_vao;
		private:
			UIComponent* m_UIParent;
			void updateMatrix();
			bool m_isDirty;
		};
	}
}
#endif // !UI_COMPONENT_H
