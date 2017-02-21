#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

#include <Fractal\include\graphics\MeshData.h>
#include <Fractal\include\graphics\Vertex.h>
namespace fractal {
	struct LoadOBJ {

		LoadOBJ() = delete;
		LoadOBJ(const LoadOBJ&) = delete;
		LoadOBJ(LoadOBJ&&) = delete;
		LoadOBJ& operator=(const LoadOBJ&) = delete;
		LoadOBJ& operator=(LoadOBJ&&) = delete;

		static fgraphics::MeshData* load(std::string fileName);
		static int* convertIndicesVectorToArray(std::vector<int> indices);
		static float convertDataToArrays(std::vector<fgraphics::Vertex>& vertices, std::vector<fmath::Vector2>& textures, std::vector<fmath::Vector3>& normals, std::vector<fmath::Point3>& position);
		static fgraphics::Vertex* processVertex(std::vector<std::string> vertex, std::vector<fgraphics::Vertex> vertices, std::vector<int> indices);
		static fgraphics::Vertex* dealWithAlreadyProcessedVertex(fgraphics::Vertex* previousVertex, int newTextureIndex, int newNormalIndex,
			std::vector<int> indices, std::vector<fgraphics::Vertex> vertices);
		static void removeUnusedVertices(std::vector<fgraphics::Vertex> vertices);

	};
	// move this somewhere later

	template<typename Out>
	void split(const std::string &s, char delim, Out result) {
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			*(result++) = item;
		}
	}


	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, std::back_inserter(elems));
		return elems;
	}

}