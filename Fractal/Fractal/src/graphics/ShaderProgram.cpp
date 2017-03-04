#include "graphics\Mesh.h"
#include "graphics\ShaderProgram.h"
#include <iostream>

namespace fractal {
	ShaderProgram::ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath) :
		m_numAttrib(0)
	{
		//get source code from filepath

		//compile shader
		m_vertexShaderID = compileShaders(vertexPath, GL_VERTEX_SHADER);;
		m_fragmentShaderID = compileShaders(fragmentPath, GL_FRAGMENT_SHADER);

		this->m_programID = glCreateProgram();

		//shader program
		glAttachShader(this->m_programID, m_vertexShaderID);
		glAttachShader(this->m_programID, m_fragmentShaderID);

		glLinkProgram(this->m_programID);
		//print linking errors
		GLint result;
		glGetProgramiv(this->m_programID, GL_LINK_STATUS, &result);
		if (!result) {

			GLchar infoLog[512];
			glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		
	}
	ShaderProgram::~ShaderProgram() {

	}
	int ShaderProgram::compileShaders(const std::string& vertexPath, const GLuint type) {

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


		int shaderID = glCreateShader(type);
		if (shaderID == 0) {
			printf("LOAD SHADER FAILED\n");
		}


		glShaderSource(shaderID, 1, &ShaderCode, nullptr);
		glCompileShader(shaderID);
		GLint success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<char> errorLog(maxLength);
			glDeleteShader(shaderID);
			//std::printf("%s\n", &(errorLog[0]));
			printf("SHADER FAILED TO COMPILE\n");
			return -1;
		}
		return shaderID;
	}
	void ShaderProgram::addAttrib(const std::string& attribName) {
		glBindAttribLocation(m_programID, m_numAttrib++, attribName.c_str());
	}
	GLuint ShaderProgram::getUniformLocation(const std::string& uniformName) {
		GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) { //returns if it doesn't exist
			printf("UNIFORM NOT FOUND\n");
		}
		return location;
	}
	void ShaderProgram::use() {

		glUseProgram(m_programID);
	}
	void ShaderProgram::destroy()
	{
		unuse();
		
		//detaching program from gpu
		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);

		//delete shaders
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		//deleting program from gpu
		glDeleteProgram(m_programID);
	}
	void ShaderProgram::storeAllAttrib(std::vector<GLuint> uniforms)
	{
		// TODO: create uniform class to work with shaders

		 //for (Uniform uniform : uniforms) {
		 //	uniform.storeUniformLocation(m_programID);
		 //}
		glValidateProgram(m_programID);


	}
	void ShaderProgram::unuse() {
		glUseProgram(0);
		for (int i = 0; i < m_numAttrib; i++) {
			glDisableVertexAttribArray(i);
		}
	}
}