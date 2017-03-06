#ifndef UNIFORM_SAMPLER_H
#define UNIFORM_SAMPLER_H

#include <Fractal\include\utils\ShaderUtils\Uniform.h>
namespace fractal {

	class UniformSampler : public Uniform {
	public:
		UniformSampler(char* name);
		void loadTextureUnit(int TextureID);
	private:
		int m_currentValue;
		bool m_used;
	};

}
#endif // !UNIFORM_SAMPLER_H
