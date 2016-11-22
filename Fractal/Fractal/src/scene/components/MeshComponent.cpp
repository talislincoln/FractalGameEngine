#include "graphics\Mesh.h"
#include "helpers\Singleton.h"
#include "scene\components\MeshComponent.h"
#include "core\systems\Window.h"
#include "core\systems\manager\SystemManager.h"
#include "graphics\Program.h"
#include <FractalMath\Matrix.h>
#include <SOIL\SOIL.h>

#include <assert.h>

namespace fractal {
	namespace fscene {
		using namespace fmath;
		MeshComponent::MeshComponent(fgraphics::Mesh* mesh) : m_mesh(mesh) {
			//build and compile shaders
			m_ourProgram = new Shader("res/shaders/vertexShader.txt", "res/shaders/fragmentShader.txt");
			//m_ourProgram.compileShaders("res/shaders/vertexShader.txt", "res/shaders/fragmentShader.txt");
			//m_ourProgram.linkShaders();
			//;w; getting the vertices
			vertices = mesh->getVertices(); //;w; cube attributes
			//vertices2 = mesh->getIndices();
			GLuint indices[] = {
				0, 1, 3, // First Triangle
				1, 2, 3  // Second Triangle
			};
			//generating array and buffer
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo); //;w; generates 1+ buffers objects, returned to access buffer object
			glGenBuffers(1, &m_ebo);

			glBindVertexArray(m_vao);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(fgraphics::Vertex), &vertices[0], GL_STATIC_DRAW); //;w; copies user-defined data into currently bound buffer

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			//;w; position attributes
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			//;w; colour attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			//;w; texcoord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			//;w; unbinds to prevent weird bugs
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			//;w; load and create texture
			//;w; texture 1
			glGenTextures(1, &m_texture1);
			glBindTexture(GL_TEXTURE_2D, m_texture1);
			//;w; set texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			//;w; set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//;w; load image, create texture, generate mipmaps
			m_image = SOIL_load_image("res/images/wooden.jpg", &IMG_WIDTH, &IMG_HEIGHT, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMG_WIDTH, IMG_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, m_image);
			glGenerateMipmap(GL_TEXTURE_2D);
			SOIL_free_image_data(m_image);
			glBindTexture(GL_TEXTURE_2D, 0); //;w; unbind texture
			printf("\n");
			printf(SOIL_last_result());
			printf("\n");
			//;w; texture 2
			glGenTextures(1, &m_texture2);
			glBindTexture(GL_TEXTURE_2D, m_texture2);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			m_image = SOIL_load_image("res/images/awesome.png", &IMG_WIDTH, &IMG_HEIGHT, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMG_WIDTH, IMG_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, m_image);
			glGenerateMipmap(GL_TEXTURE_2D);
			SOIL_free_image_data(m_image);
			glBindTexture(GL_TEXTURE_2D, 0);
			printf("\n");
			printf(SOIL_last_result());
			printf("\n");
		}

		MeshComponent::~MeshComponent() {

		}

		/**
		Init the mesh component.
		*/
		bool MeshComponent::initialize() {

			return m_mesh != nullptr;
		}

		/**
		draw the mesh components based on the vertices provided.
		*/
		void MeshComponent::draw() {
			//;w; clear colour buffer
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			//;w; shader
			m_ourProgram->use();
			//;w; bind texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture1);
			glUniform1i(glGetUniformLocation(m_ourProgram->getProgramID(), "ourTexture1"), 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_texture2);
			glUniform1i(glGetUniformLocation(m_ourProgram->getProgramID(), "ourTexture2"), 1);
			//;w; transformations
			Matrix4 transform;
			transform = Matrix4::translate(Vector3(0.5f, -0.5f, 0.0f));
			transform = Matrix4::rotate(SDL_GetTicks() * 0.05, 0.0f, 0.0f, 1.0f);
			//;w; get matrix uniform location and set matrix
			GLint transformLoc = glGetUniformLocation(m_ourProgram->getProgramID(), "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform);
			//;w; draw container
			glBindVertexArray(m_vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			//unbinding vertex array
			glBindVertexArray(0);
		}

		void MeshComponent::update() {

		}

		bool MeshComponent::shutdown() {
			//cleaning/deleting the buffers and array within the gpu
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_vbo);
			glDeleteBuffers(1, &m_ebo);
			return true;
		}
	}
}
