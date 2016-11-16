#include "graphics\Mesh.h"
#include "scene\components\MeshComponent.h"

#include <assert.h>

namespace fractal {
	namespace fscene {
		MeshComponent::MeshComponent(fgraphics::Mesh* mesh) : m_mesh(mesh) {

			//const int size = mesh->getVertices().size() * 3;
			//GLfloat vertices[9];

			//int counter = 0;
			//
			//for (unsigned int i = 0; i < mesh->getVertices().size(); i++) {
			//	vertices[counter++] = mesh->getVertices()[i].position.x;
			//	vertices[counter++] = mesh->getVertices()[i].position.y;
			//	vertices[counter++] = mesh->getVertices()[i].position.z;
			//}

			//// Vertex shader
			//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
			//glCompileShader(vertexShader);
			//// Check for compile time errors
			//GLint success;
			//GLchar infoLog[512];
			//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			//if (!success)
			//{
			//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			//}
			//// Fragment shader
			//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
			//glCompileShader(fragmentShader);
			//// Check for compile time errors
			//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			//if (!success)
			//{
			//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			//}
			//// Link shaders
			//shaderProgram = glCreateProgram();
			//glAttachShader(shaderProgram, vertexShader);
			//glAttachShader(shaderProgram, fragmentShader);
			//glLinkProgram(shaderProgram);
			//// Check for linking errors
			//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			//if (!success) {
			//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			//}
			//glDeleteShader(vertexShader);
			//glDeleteShader(fragmentShader);

			//glGenVertexArrays(1, &m_vao);
			//glBindVertexArray(m_vao);
			//
			//glGenBuffers(1, &m_vbo);
			//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
			//glEnableVertexAttribArray(0);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindVertexArray(0);
		}

		MeshComponent::~MeshComponent() {

		}

		bool MeshComponent::initialize() {
			
			return m_mesh != nullptr;
		}

		void MeshComponent::draw() {
			////m_mesh->draw();
			//glUseProgram(shaderProgram);
			//glBindVertexArray(m_vao);
			////int indices[3] = { 0,1,2 };			//glDrawArrays(GL_TRIANGLES, 0, 3);
			////glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			//glBindVertexArray(0);
			////clear screen
			
		}

		void MeshComponent::update() {

		}

		bool MeshComponent::shutdown() {
			/*glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_vbo);*/
			return true;
		}
	}
}
