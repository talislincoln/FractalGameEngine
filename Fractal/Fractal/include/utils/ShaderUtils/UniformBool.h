#ifndef UNIFORMBOOL_H
#define UNIFORMBOOL_H
#include <Fractal\include\utils\ShaderUtils\Uniform.h>
namespace fractal {

	class UniformBool : public Uniform {
	public:
		UniformBool(char* name);
		void loadBool(bool boolean);
	private:
		bool m_currentBool;
		bool m_used = false;
	};

}
#endif // !UniformBool_H

