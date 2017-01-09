#ifndef PROGRAM_H
#define PROGRAM_H
#include <string>
#include <fstream>
#include <sstream>

#include <Fractal\include\graphics\Mesh.h>
#include <Fractal\include\utils\IOManager.h>


namespace fractal {
	class Shader {
	public:
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
		/*~Shader();
		void compileShaders(const std::string& vertexPath, const std::string& fragmentPath);
		void linkShaders();
		void addAttrib(const std::string& attribName);
		GLuint getUniformLocation(const std::string& uniformName);
		void unuse();*/
		void use();
		inline const GLuint getProgramID() const {
			return m_programID;
		}

	private:
		GLuint m_programID;
		/*int m_numAttrib;
		void m_compileShader(const std::string& filepath, GLuint& id);
		GLuint m_vertexShaderID;
		GLuint m_fragShaderID;*/
	};
}

#endif