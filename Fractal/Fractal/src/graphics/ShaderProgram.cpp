#include "graphics\ShaderProgram.h"
#include <iostream>

namespace fractal {
	ShaderProgram::ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath, const unsigned int size, ...) :
		m_numAttrib(0)
	{
		va_list ap;
		std::vector<char*> attribName;
		va_start(ap, size);
		for (unsigned int i = 0; i < size; i++) {
			attribName.push_back(va_arg(ap, char*));
		}

		va_end(ap);
		//get source code from filepath

		//compile shader
		std::string path = "res/" + (std::string)vertexPath + ".vert";
		GLuint m_vertexShaderID = compileShaders(path, GL_VERTEX_SHADER);
		path = "res/" + (std::string)fragmentPath + ".frag";
		GLuint m_fragmentShaderID = compileShaders(path, GL_FRAGMENT_SHADER);

		this->m_programID = glCreateProgram();

		//shader program
		glAttachShader(this->m_programID, m_vertexShaderID);
		glAttachShader(this->m_programID, m_fragmentShaderID);

		addAttrib(attribName);

		glLinkProgram(this->m_programID);
		//print linking errors
		GLint result;
		glGetProgramiv(this->m_programID, GL_LINK_STATUS, &result);
		if (!result) {

			GLchar infoLog[512];
			glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		//detaching program from gpu
		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);

		//delete shaders
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

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
			std::printf("%s\n", &(errorLog[0]));
			printf("SHADER FAILED TO COMPILE\n");
			return -1;
		}
		return shaderID;
	}
	void ShaderProgram::addAttrib(std::vector<char*>& attribName) {
		for (size_t i = 0; i < attribName.size(); i++) {
			glBindAttribLocation(m_programID, m_numAttrib, attribName[i]);
			m_numAttrib++;
		}
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
		for (int i = 0; i < m_numAttrib; i++) {
			glEnableVertexAttribArray(i);
		}
	}
	void ShaderProgram::destroy()
	{
		unuse();
		
		//deleting program from gpu
		glDeleteProgram(m_programID);
	}
	void ShaderProgram::storeUniformLocations(const std::vector<Uniform*> uniforms)
	{
		for (unsigned int i = 0; i < uniforms.size(); i++) {
			uniforms[i]->storeUniformLocation(this->m_programID);
		}
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
		for (int i = 0; i < m_numAttrib; i++) {
			glDisableVertexAttribArray(i);
		}
		glUseProgram(0);
	}
}