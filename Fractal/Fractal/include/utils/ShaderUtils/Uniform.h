#ifndef UNIFORM_H
#define UNIFORM_H
#include <string>
#include <GL\glew.h>

namespace fractal {
	class Uniform {
	public:
		Uniform(std::string& name);
		virtual void storeUniformLocation(int programID);
		virtual inline int getLocation() {
			return m_location;
		}

	private:
		static const int NOT_FOUND = -1;
		std::string m_name;
		int m_location;


	};
}
#endif // !UNIFORM_H
