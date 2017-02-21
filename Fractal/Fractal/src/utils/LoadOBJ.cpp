#pragma once
#include "utils\LoadOBJ.h"
#include <iostream>
#include <fstream>
namespace fractal {
	fgraphics::MeshData* LoadOBJ::load(std::string fileName) {
		using namespace std;
		using namespace fmath;
		using namespace fgraphics;
		ifstream reader;
		reader.open(fileName, ios::out);
		string line;
		vector<fgraphics::Vertex> vertices;
		vector<Vector2> textures;
		vector<Vector3> normals;
		vector<int> indices;
		while (true) {
			getline(reader, line);
			vector<string> currentLine;
			if (strncmp(line.c_str(), "v ", 2)) {
				currentLine = split(line, ' ');
				Point3 vertex = Point3((float)stod(currentLine[1]),
					(float)stod(currentLine[2]), (float)stod(currentLine[3]));
				vertices.push_back(Vertex(vertex, vertices.size()));

			}
			else if (strncmp(line.c_str(), "vt ", 3)) {
				currentLine = split(line, ' ');
				Vector2 texture = Vector2((float)stod(currentLine[1]),
					(float)stod(currentLine[2]));
				textures.push_back(texture);
			}
			else if (strncmp(line.c_str(), "vn ", 3)) {

				currentLine = split(line, ' ');
				Vector3 normal = Vector3((float)stod(currentLine[1]),
					(float)stod(currentLine[2]), (float)stod(currentLine[3]));
				normals.push_back(normal);
			}
			else if (strncmp(line.c_str(), "f ", 2)) {
				break;
			}
		}
		while (line.empty() && strncmp(line.c_str(), "f ", 2)) {

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
			getline(reader, line);
		}
		reader.close();
		removeUnusedVertices(vertices);
		std::vector<fmath::Point3> position;
		float furthest = convertDataToArrays(vertices, textures, normals, position);
		return new MeshData(position, textures, normals, indices, furthest, vertices.size());
	}
	fgraphics::Vertex* LoadOBJ::processVertex(std::vector<std::string> vertex, std::vector<fgraphics::Vertex> vertices, std::vector<int> indices) {
		using namespace fgraphics;
		int index = std::stoi(vertex[0]) - 1;
		Vertex* currentVertex = &vertices[index];

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

	int* LoadOBJ::convertIndicesVectorToArray(std::vector<int> indices) {
		return &indices[0];
	}

	float LoadOBJ::convertDataToArrays(std::vector<fgraphics::Vertex>& vertices, std::vector<fmath::Vector2>& textures, std::vector<fmath::Vector3>& normals, std::vector<fmath::Point3>& position) {
		using namespace fmath;
		float furthestPoint = 0;
		std::vector<fgraphics::Vertex> newVertices;
		std::vector<fmath::Vector2> newTexture;
		std::vector<fmath::Vector3> newNormal;

		for (size_t i = 0; i < vertices.size(); i++) {
			fgraphics::Vertex currentVertex = vertices[i];

			if (currentVertex.getLength() > furthestPoint) {
				furthestPoint = currentVertex.getLength();
			}
			Vector2 textureCoord = textures[currentVertex.getTextureIndex()];
			Vector3 normalVector = normals[currentVertex.getNormalIndex()];
			newVertices.push_back(currentVertex);
			newTexture.push_back(textureCoord);
			newNormal.push_back(normalVector);
			position.push_back(currentVertex.position);
		}
		vertices = newVertices;
		textures = newTexture;
		normals = newNormal;

		return furthestPoint;
	}

	fgraphics::Vertex* LoadOBJ::dealWithAlreadyProcessedVertex(fgraphics::Vertex* previousVertex, int newTextureIndex, int newNormalIndex,
		std::vector<int> indices, std::vector<fgraphics::Vertex> vertices) {
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
				vertices.push_back(*duplicateVertex);
				indices.push_back(duplicateVertex->getIndex());
				return duplicateVertex;
			}

		}
	}

	void LoadOBJ::removeUnusedVertices(std::vector<fgraphics::Vertex> vertices) {
		for (fgraphics::Vertex vertex : vertices) {
			vertex.averageTangents();
			if (!vertex.isSet()) {
				vertex.setTextureIndex(0);
				vertex.setNormalIndex(0);
			}
		}
	}
}