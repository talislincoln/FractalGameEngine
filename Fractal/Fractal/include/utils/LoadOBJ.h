#ifndef _LOAD_OBJ_H
#define _LOAD_OBJ_H


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

		static fgraphics::MeshData* load(const std::string fileName);
		static fgraphics::MeshData* load(const char* fileName);
		static int* convertIndicesVectorToArray(std::vector<int>& indices);
		static float convertDataToArrays(std::vector<fgraphics::Vertex*>& vertices, std::vector<fmath::Vector2>& textures, std::vector<fmath::Vector3>& normals);
		static fgraphics::Vertex* processVertex(const std::vector<std::string>& vertex, std::vector<fgraphics::Vertex*>& vertices, std::vector<int>& indices);
		static fgraphics::Vertex* dealWithAlreadyProcessedVertex(fgraphics::Vertex* previousVertex, int newTextureIndex, int newNormalIndex,
			std::vector<int>& indices, std::vector<fgraphics::Vertex*>& vertices);
		static void removeUnusedVertices(std::vector<fgraphics::Vertex*>& vertices);


		template<typename Out>
		static void split(const std::string &s, char delim, Out result) {
			std::stringstream ss;
			ss.str(s);
			std::string item;
			while (std::getline(ss, item, delim)) {
				if (!item.empty()) {
					*(result++) = item;
				}
			}
		}
		static std::vector<std::string> split(const std::string &s, char delim) {
			std::vector<std::string> elems;
			split(s, delim, std::back_inserter(elems));
			return elems;
		}

	};
	// move this somewhere later

}
#endif // !_LOAD_OBJ_H