#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H
#include "scene\Component.h"
#include "interfaces\IDrawable.h"
#include "graphics\materials\DefaultUIMaterial.h"
namespace fractal {
	namespace fHUD {
		class UIComponent : public fscene::Component, public IDrawable {
		public:
			UIComponent(fgraphics::Material* m = new fgraphics::DefaultUIMaterial());
			~UIComponent();
			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();
			virtual void draw();
		protected:
			fgraphics::Material* m_material;
		private:
			void createVAO();
			void storeDataInVAO();
			void unbindVAO() const;


			GLuint m_vao;
			//list of vertices to be deleted from the gpu
			std::vector<GLuint> m_vbos;
		};
	}
}
#endif // !UI_COMPONENT_H
