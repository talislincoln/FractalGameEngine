#include "graphics\Mesh.h"
#include "graphics\Program.h"
#include <iostream>

namespace fractal {
	Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
		//get source code from filepath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		//checks if it can throw exceptions
		vShaderFile.exceptions(std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::badbit);
		try {
			//open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//read's file into stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//close bandlers
			vShaderFile.close();
			fShaderFile.close();
			//converts stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			printf("SHADER ERROR: NOT READ");
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();
		//compile shaders
		GLuint vertex, fragment;
		GLint result;
		GLchar infoLog[512];
		//vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		//print any compile errors
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			printf("ERROR: VERTEX COMPILATION FAILED");
		}
		//fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		//print any errors
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			printf("ERROR: FRAGMENT COMPILATION FAILED");
		}
		//shader program
		this->m_programID = glCreateProgram();
		glAttachShader(this->m_programID, vertex);
		glAttachShader(this->m_programID, fragment);
		glLinkProgram(this->m_programID);
		//print linking errors
		glGetProgramiv(this->m_programID, GL_LINK_STATUS, &result);
		if (!result) {
			glGetProgramInfoLog(this->m_programID, 512, NULL, infoLog);
			printf("ERROR: LINKING FAILED");
		}
		//delete shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	//Shader::~Shader() {

	//}
	//void Shader::compileShaders(const std::string& vertexPath, const std::string& fragmentPath) {
	//	m_programID = glCreateProgram();
	//	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//	if (m_vertexShaderID == 0) {
	//		printf("VERTEX FAILED\n");
	//	}
	//	m_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	//	if (m_vertexShaderID == 0) {
	//		printf("FRAGMENT FAILED\n");
	//	}
	//	m_compileShader(vertexPath, m_vertexShaderID);
	//	m_compileShader(fragmentPath, m_fragShaderID);
	//}
	//void Shader::linkShaders() {
	//	glAttachShader(m_programID, m_vertexShaderID);
	//	glAttachShader(m_programID, m_fragShaderID);
	//	glLinkProgram(m_programID);
	//	GLint isLinked = 0;
	//	glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
	//	if (isLinked == GL_FALSE) {
	//		GLint maxLength = 0;
	//		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);
	//		std::vector<GLchar> errorLog(maxLength);
	//		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);
	//		glDeleteProgram(m_programID);
	//		glDeleteShader(m_vertexShaderID);
	//		glDeleteShader(m_fragShaderID);
	//		//std::printf("%s\n", &(errorLog[0]));
	//		printf("LINK FAILED\n");
	//	}
	//	glDetachShader(m_programID, m_vertexShaderID);
	//	glDetachShader(m_programID, m_fragShaderID);
	//	glDeleteShader(m_vertexShaderID);
	//	glDeleteShader(m_fragShaderID);
	//}
	//void Shader::addAttrib(const std::string& attribName) {
	//	glBindAttribLocation(m_programID, m_numAttrib++, attribName.c_str());
	//}
	//GLuint Shader::getUniformLocation(const std::string& uniformName) {
	//	GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
	//	if (location == GL_INVALID_INDEX) { //returns if it doesn't exist
	//		printf("UNIFORM NOT FOUND\n");
	//	}
	//	return location;
	//}
	void Shader::use() {
		glUseProgram(m_programID);
	}
	//void Shader::unuse() {
	//	glUseProgram(0);
	//	for (int i = 0; i < m_numAttrib; i++) {
	//		glDisableVertexAttribArray(i);
	//	}
	//}
	//void Shader::m_compileShader(const std::string& filepath, GLuint& id) {
	//	std::ifstream vertexFile(filepath);
	//	if (vertexFile.fail()) {
	//		//perror(filepath.c_str());
	//		printf("FAILED TO OPEN SHADERS\n");
	//	}
	//	std::string fileContents = "";
	//	std::string line;
	//	while (std::getline(vertexFile, line)) {//each line obtained is pos
	//		fileContents += line + "\n";
	//	}
	//	vertexFile.close();
	//	const char* contentstr = fileContents.c_str();
	//	glShaderSource(id, 1, &contentstr, nullptr);
	//	glCompileShader(id);
	//	GLint success = 0;
	//	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	//	if (success == GL_FALSE) {
	//		GLint maxLength = 0;
	//		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
	//		std::vector<char> errorLog(maxLength);
	//		glDeleteShader(id);
	//		//std::printf("%s\n", &(errorLog[0]));
	//		printf("SHADER FAILED TO COMPILE\n");
	//		return;
	//	}
	//}
}