
#include "utils\LoadOBJ.h"
#include <iostream>
#include <fstream>
#include <assert.h>
namespace fractal {
	fgraphics::MeshData* LoadOBJ::load(const char*& fileName) {
		std::string temp(fileName);
		return load(temp);
	}

	fgraphics::MeshData* LoadOBJ::load(const std::string& fileName) {
		using namespace std;
		using namespace fmath;
		using namespace fgraphics;
		ifstream reader;

		reader.open("res/" + fileName + ".obj");
		if (!reader.is_open()) {
			printf("failed  %s", &fileName[0]); // need debug~
			assert(reader);
		}
		string line;
		vector<fgraphics::Vertex*> vertices;
		vector<Vector2> textures;
		vector<Vector3> normals;
		vector<int> indices;
		while (true) {
			getline(reader, line);
			vector<string> currentLine;
			if (strncmp(line.c_str(), "v ", 2) == 0) {
				currentLine = split(line, ' ');
				Point3 vertex = Point3((float)stod(currentLine[1]),
					(float)stod(currentLine[2]), (float)stod(currentLine[3]));
				vertices.push_back(new Vertex(vertex, vertices.size()));
			}
			else if (strncmp(line.c_str(), "vt ", 3) == 0) {
				currentLine = split(line, ' ');
				Vector2 texture = Vector2((float)stod(currentLine[1]),
					(float)stod(currentLine[2]));
				textures.push_back(texture);
			}
			else if (strncmp(line.c_str(), "vn ", 3) == 0) {

				currentLine = split(line, ' ');
				Vector3 normal = Vector3((float)stod(currentLine[1]),
					(float)stod(currentLine[2]), (float)stod(currentLine[3]));
				normals.push_back(normal);
			}
			else if (strncmp(line.c_str(), "f ", 2) == 0) {
				break;
			}
			else if (reader.eof()) {
				assert(reader);
			}
			//else  break  // need debug~
		}

		while (!reader.eof()) {
			if (strncmp(line.c_str(), "f ", 2) == 0) {
				vector<string> currentLine;
				currentLine = split(line, ' ');
				vector<string> vertex1;
				vertex1 = split(currentLine[1], '/');
				vector<string> vertex2;
				vertex2 = split(currentLine[2], '/');
				vector<string> vertex3;
				vertex3 = split(currentLine[3], '/');
				processVertex(vertex1, vertices, indices);
				processVertex(vertex2, vertices, indices);
				processVertex(vertex3, vertices, indices);
			}
			getline(reader, line);
		}
		reader.close();
		removeUnusedVertices(vertices);
		std::vector<fmath::Vector3> position;
		float furthest = convertDataToArrays(vertices, textures, normals, position);
		cleanUp(vertices);
		return new MeshData(position, textures, normals, indices, furthest, vertices.size());
	}
	fgraphics::Vertex* LoadOBJ::processVertex(const std::vector<std::string>& vertex, std::vector<fgraphics::Vertex*> &vertices, std::vector<int>& indices) {
		using namespace fgraphics;
		int index = std::stoi(vertex[0]) - 1;
		Vertex* currentVertex = vertices[index];

		int textureIndex = std::stoi(vertex[1]) - 1;
		int normalIndex = std::stoi(vertex[2]) - 1;
		if (!currentVertex->isSet()) {
			currentVertex->setTextureIndex(textureIndex);
			currentVertex->setNormalIndex(normalIndex);
			indices.push_back(index);
			return currentVertex;
		}
		else {
			return dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
		}
	}

	float LoadOBJ::convertDataToArrays(std::vector<fgraphics::Vertex*>& vertices, std::vector<fmath::Vector2>& textures, std::vector<fmath::Vector3>& normals, std::vector<fmath::Vector3>& position) {
		using namespace fmath;
		float furthestPoint = 0;
		std::vector<Vector2> newTexture;
		std::vector<Vector3> newNormal;

		for (size_t i = 0; i < vertices.size(); i++) {
			fgraphics::Vertex* currentVertex = vertices[i];

			if (currentVertex->getLength() > furthestPoint) {
				furthestPoint = currentVertex->getLength();
			}
			Vector2 textureCoord = textures[currentVertex->getTextureIndex()];
			textureCoord.y = 1 - textureCoord.y;
			Vector3 normalVector = normals[currentVertex->getNormalIndex()];
			position.push_back(currentVertex->getPosition());
			newTexture.push_back(textureCoord);
			newNormal.push_back(normalVector);
		}
		textures = newTexture;
		normals = newNormal;

		return furthestPoint;
	}

	fgraphics::Vertex* LoadOBJ::dealWithAlreadyProcessedVertex(fgraphics::Vertex* previousVertex, int newTextureIndex, int newNormalIndex,
		std::vector<int>& indices, std::vector<fgraphics::Vertex*>& vertices) {
		if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
			indices.push_back(previousVertex->getIndex());
			return previousVertex;
		}
		else {
			fgraphics::Vertex* anotherVertex = previousVertex->getDuplicateVertex();
			if (anotherVertex != nullptr) {
				return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
			}
			else {
				fgraphics::Vertex* duplicateVertex = new fgraphics::Vertex(previousVertex->getPosition(), vertices.size());
				duplicateVertex->setTextureIndex(newTextureIndex);
				duplicateVertex->setNormalIndex(newNormalIndex);
				previousVertex->setDuplicateVertex(duplicateVertex);
				vertices.push_back(duplicateVertex);
				indices.push_back(duplicateVertex->getIndex());
				return duplicateVertex;
			}

		}
	}

	void LoadOBJ::removeUnusedVertices(std::vector<fgraphics::Vertex*>& vertices) {
		for (fgraphics::Vertex* vertex : vertices) {
			vertex->averageTangents();
			if (!vertex->isSet()) {
				vertex->setTextureIndex(0);
				vertex->setNormalIndex(0);
			}
		}
	}

	void LoadOBJ::cleanUp(std::vector<fgraphics::Vertex*>& vertices)
	{
		for (fgraphics::Vertex* temp : vertices) {
			delete(temp);
		}
		vertices.clear();
	}
}