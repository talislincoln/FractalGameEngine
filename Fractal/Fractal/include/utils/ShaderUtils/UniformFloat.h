#ifndef UNIFORMFLOAT_H
#define UNIFORMFLOAT_H
#include <Fractal\include\utils\ShaderUtils\Uniform.h>
namespace fractal {

	class UniformFloat : public Uniform {

	public:
		UniformFloat(std::string& name);
		void loadFloat(float f);
	private:
		float m_currentValue;
		bool m_used = false;
	};

}
#endif // !UNIFORMFLOAT_H

