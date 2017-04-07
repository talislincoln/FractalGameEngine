#ifndef _TERRAINCOMPONENT
#define _TERRAINCOMPONENT

#include <Fractal\include\scene\Component.h>
#include <FractalMath\Vector.h>
#include "graphics\materials\DefaultMeshMaterial.h"
#include <Fractal\include\interfaces\IDrawable.h>
namespace fractal {
	namespace fscene {

		class TerrainComponent :
			public fscene::Component, public IDrawable
		{
		public:
			TerrainComponent(const std::string& name = "" ,const fgraphics::Material* m = new fgraphics::DefaultMaterial(),
				float height = -0.5f );
			virtual void update();
			virtual bool initialize();
			virtual bool shutdown();
			virtual void draw();
			virtual ~TerrainComponent();


			inline void set(float x, float z, float height) {
				this->height = height;
			}
			inline float get(float x, float z) const {
				return height;
			}
			inline void setHeight(float x, float z, float height) {
				set(x, z, height);
			}
			inline void setHeight(const fmath::Vector3& pos, float height) {
				set(pos.x, pos.z, height);
			}
			inline float getHeight(float x, float z) const {
				return get(x, z);
			}
			inline float getHeight(const fmath::Vector3& pos) const {
				return get(pos.x, pos.z);
			}
			inline const fmath::Vector3& getNornmal(float x, float z) const {
				return m_normal;
			}
			inline const fmath::Vector3& getNornmal(const fmath::Vector3& pos) const{
				return m_normal;
			}
		private:
			float height;
			const fgraphics::Material* m_TerrainMaterial;
			fmath::Vector2 m_Size;
			fmath::Vector3 m_Position;
			fmath::Vector3 m_normal;
		};

	}
}


#endif // !_TERRAINCOMPONENT
