#include "graphics\Mesh.h"
#include "graphics\Program.h"
#include <iostream>

namespace fractal {
	Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
		//get source code from filepath

		//compile shader
		GLuint vertexShaderID = compileShaders(vertexPath, GL_VERTEX_SHADER);;
		GLuint fragmentShaderID = compileShaders(fragmentPath, GL_FRAGMENT_SHADER);

		this->m_programID = glCreateProgram();

		//shader program
		glAttachShader(this->m_programID, vertexShaderID);
		glAttachShader(this->m_programID, fragmentShaderID);

		glLinkProgram(this->m_programID);
		//print linking errors
		GLint result;
		glGetProgramiv(this->m_programID, GL_LINK_STATUS, &result);
		if (!result) {

			GLchar* infoLog;
			glGetProgramInfoLog(this->m_programID, 512, NULL, infoLog);
			printf("ERROR: LINKING FAILED");
		}
		//delete shaders
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	Shader::~Shader() {

	}
	int Shader::compileShaders(const std::string& vertexPath, const GLuint type) {

		std::string code;
		std::ifstream ShaderFile;

		ShaderFile.exceptions(std::ifstream::badbit);
		//checks if it can throw exceptions
		try {
			//open files
			ShaderFile.open(vertexPath);
			std::stringstream vShaderStream, fShaderStream;
			//read's file into stream
			vShaderStream << ShaderFile.rdbuf();
			//close bandlers
			ShaderFile.close();
			//converts stream into string
			code = vShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			printf("SHADER ERROR: NOT READ");
		}

		const GLchar* ShaderCode = code.c_str();


		int ShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (ShaderID == 0) {
			printf("LOAD SHADER FAILED\n");
		}


		glShaderSource(ShaderID, 1, &ShaderCode, nullptr);
		glCompileShader(ShaderID);
		GLint success = 0;
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<char> errorLog(maxLength);
			glDeleteShader(ShaderID);
			//std::printf("%s\n", &(errorLog[0]));
			printf("SHADER FAILED TO COMPILE\n");
			return -1;
		}
		return ShaderID;
	}
	void Shader::addAttrib(const std::string& attribName) {
		glBindAttribLocation(m_programID, m_numAttrib++, attribName.c_str());
	}
	GLuint Shader::getUniformLocation(const std::string& uniformName) {
		GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) { //returns if it doesn't exist
			printf("UNIFORM NOT FOUND\n");
		}
		return location;
	}
	void Shader::use() {
		glUseProgram(m_programID);
	}
	void Shader::destroy()
	{
		unuse();
		glDeleteProgram(m_programID);
	}
	void Shader::storeAllAttrib(std::vector<GLuint> uniforms)
	{
		// TODO: create uniform class to work with shaders

		 //for (Uniform uniform : uniforms) {
		 //	uniform.storeUniformLocation(m_programID);
		 //}
		glValidateProgram(m_programID);


	}
	void Shader::unuse() {
		glUseProgram(0);
		for (int i = 0; i < m_numAttrib; i++) {
			glDisableVertexAttribArray(i);
		}
	}
}