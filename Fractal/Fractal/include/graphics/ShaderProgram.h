#ifndef PROGRAM_H
#define PROGRAM_H
#include <string>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include <Fractal\include\utils\IOManager.h>
#include <Fractal\include\utils\ShaderUtils\Uniform.h>
#include <Fractal\include\utils\ShaderUtils\UniformBool.h>
#include <Fractal\include\utils\ShaderUtils\UniformFloat.h>
#include <Fractal\include\utils\ShaderUtils\UniformMatrix.h>
#include <Fractal\include\utils\ShaderUtils\UniformSampler.h>
#include <Fractal\include\utils\ShaderUtils\UniformVector2.h>
#include <Fractal\include\utils\ShaderUtils\UniformVector3.h>
#include <Fractal\include\utils\ShaderUtils\UniformVector4.h>

namespace fractal {
	class ShaderProgram {
	public:
		ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath, const unsigned int size, ...);
		~ShaderProgram();
		GLuint getUniformLocation(const std::string& uniformName);
		void unuse();
		void use();
		void destroy();
		void storeUniformLocations(const unsigned int size, ...);
		inline const GLuint getProgramID() const {
			return m_programID;
		}
	protected:
		void addAttrib(std::vector<char*>& attribName);
		void storeAllAttrib(std::vector<GLuint> uniforms);

	private:
		int compileShaders(const std::string& Path, const GLuint Type);
		GLuint m_programID;
		int m_numAttrib;
	};
}

#endif