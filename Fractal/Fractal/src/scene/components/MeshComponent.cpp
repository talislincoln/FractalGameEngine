#include "graphics\Mesh.h"
#include "helpers\Singleton.h"
#include "scene\components\MeshComponent.h"
#include "core\systems\Window.h"
#include "core\systems\manager\SystemManager.h"
#include  <FractalMath\Matrix.h>

#include <assert.h>

namespace fractal {
	namespace fscene {
		using namespace fmath;
		MeshComponent::MeshComponent(fgraphics::Mesh* mesh) : m_mesh(mesh) {
			//;w; allow use of more modern techniques for managing openGL
			glewExperimental = GL_TRUE;
			//;w; initializes glew
			if (glewInit() != GLEW_OK) {
				fprintf(stderr, "GLEW FAILED");
			}
			//;w; size of rendering window
			glViewport(0, 0, WIDTH, HEIGHT);
			//;W; lets us check the depth of an object's vertices to see if it's in front or behind another vertex
			glEnable(GL_DEPTH_TEST);
			//;w; getting the vertices
			vertices = mesh->getVertices(); //;w; cube attributes
			vertices2 = mesh->getVertices(); //;w; cube positions
			//generating array and buffer
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo); //;w; generates 1+ buffers objects, returned to access buffer object
			
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(fgraphics::Vertex), &vertices[0], GL_STATIC_DRAW); //;w; copies user-defined data into currently bound buffer
			//;w; position attributes
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(fgraphics::Vertex), (GLvoid*)0); 
			glEnableVertexAttribArray(0);
			//;w; unbinds to prevent weird bugs
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
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
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//;w; create transformations
			Matrix4 view;
			Matrix4 projection;
			view = Matrix4::translate(0.0f, 0.0f, -3.0f); 
			projection = Matrix4::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1, 1000.0f);
			//;w; get their uniform location need shader.h
			//GLint modelLoc = glGetUniformLocation(ourshader.Program, "model");
			//GLint viewLoc = glGetUniformLocation(ourshader.progam, "view");
			//GLint projLoc = glGetUniformLocation(ourshader.program, "projection");
			//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view); //glm::value_ptr equivalent
			//glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection);
			//binding vertex array
			glBindVertexArray(m_vao);
			for (int i = 0; i < 10; i++) {
				//;w; 
				Matrix4 model;
				model = Matrix4::translate(vertices2[i].position.x, vertices2[i].position.y, vertices2[i].position.z);
				GLfloat angle = 20.0f * i;
				model = Matrix4::rotate(angle, 1.0f, 0.3f, 0.5f);
				/*glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);*/
				//;w; generates all sides of a cube
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			//unbinding vertex array
			glBindVertexArray(0);
		}

		void MeshComponent::update() {

		}

		bool MeshComponent::shutdown() {
			//cleaning/deleting the buffers and array within the gpu
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_vbo);
			return true;
		}
	}
}
