#ifndef PROGRAM_H
#define PROGRAM_H
#include <string>
#include <fstream>
#include <sstream>

#include <Fractal\include\utils\IOManager.h>


namespace fractal {
	class Shader {
	public:
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
		~Shader();
		int compileShaders(const std::string& Path, const GLuint Type);
		void addAttrib(const std::string& attribName);
		GLuint getUniformLocation(const std::string& uniformName);
		void unuse();
		void use();
		void destroy();
		inline const GLuint getProgramID() const {
			return m_programID;
		}
	protected:
		void storeAllAttrib(std::vector<GLuint> uniforms);

	private:
		GLuint m_programID;
		int m_numAttrib;
	};
}

#endif