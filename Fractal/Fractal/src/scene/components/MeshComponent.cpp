#include "graphics\Mesh.h"
#include "helpers\Singleton.h"
#include "scene\components\MeshComponent.h"
#include "core\systems\Window.h"
#include "core\systems\manager\SystemManager.h"
#include "graphics\Program.h"
//#include "scene\objects\FreeCamera.h"
#include <FractalMath\Matrix.h>
#include <SOIL\SOIL.h>
#include "scene\GameObject.h"
#include "scene\components\TransformComponent.h"

#include <assert.h>

namespace fractal {
	namespace fscene {
		using namespace fmath;
		MeshComponent::MeshComponent(fgraphics::Mesh* mesh) : m_mesh(mesh) {
			///;W; STORES MESH, TEXTURE, SHADERS
			///;W; SETUP OF VAO, VBO, EBO, TEXTURES
			///;W; GENERAL CODE

			//build and compile shaders


			m_ourProgram = new Shader("res/shaders/vertexShader.txt", "res/shaders/fragmentShader.txt");
			m_cubeShader = new Shader("res/shaders/cubeVert.txt", "res/shaders/cubeFrag.txt");
			//;w; getting the vertices
			vertices = mesh->getVertices(); //;w; cube attributes
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo); //;w; generates 1+ buffers objects, returned to access buffer object

			glBindVertexArray(m_vao);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(fmath::Point3), &vertices[0], GL_STATIC_DRAW); //;w; copies user-defined data into currently bound buffer
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			//;w; texcoord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			//;w; unbinds to prevent weird bugs
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

		bool MeshComponent::initialize() {
			createVAO();
			storeDataInVAO();
			unbindVAO();

			return true;
		}

		void MeshComponent::draw() {
			glBindVertexArray(m_vao);
			glEnableVertexAttribArray(0);
			glDrawArrays(GL_TRIANGLES, 0, m_mesh->getVertices().size());
			glDisableVertexAttribArray(0);
			glBindVertexArray(0);
		}

		void MeshComponent::update() {

		}

		bool MeshComponent::shutdown() {
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_vbo);

			return true;
		}

		void MeshComponent::createVAO() {
			//first argument specifies the number of arrays to generate
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);
		}

		void MeshComponent::storeDataInVAO() {
			//create 1 vbo
			glGenBuffers(1, &m_vbo);

			//start using this vbo
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			glBufferData(GL_ARRAY_BUFFER, m_mesh->getVertices().size() * sizeof(fgraphics::Vertex), &m_mesh->getVertices(), GL_STATIC_DRAW);

			// the meaning of each attribute
			// 1 - attribute position
			// 2 - the size of the array (3 because we only have x,y,z for now
			// 3 - the type of the data being passed in
			// 4 - if the data is normalized
			// 5 - distance between each vertices
			// 6 - offset (should it start at the begining of the data
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			//unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void MeshComponent::unbindVAO() {
			glBindVertexArray(0);
		}
	}
}