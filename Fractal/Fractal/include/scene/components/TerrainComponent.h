#ifndef _TERRAINCOMPONENT
#define _TERRAINCOMPONENT

#include <Fractal\include\scene\Component.h>
#include <FractalMath\Vector.h>
namespace fractal {
	namespace fscene {

		class TerrainComponent :
			public fscene::Component
		{
		public:
			TerrainComponent(float height = -0.5f, const std::string& name = "");
			virtual void update() {	}
			bool initialize();
			bool shutdown() { return true; }
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
				return normal;
			}
			inline const fmath::Vector3& getNornmal(const fmath::Vector3& pos) const{
				return normal;
			}
		private:
			float height;
			fmath::Vector3 normal;
		};

	}
}


#endif // !_TERRAINCOMPONENT
