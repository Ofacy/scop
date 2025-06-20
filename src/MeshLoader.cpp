#include "MeshLoader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstring>

Mesh MeshLoader::loadMesh(const std::string& filePath) {
	Mesh mesh;

	// Open the file
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open mesh file: " + filePath);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string command;
		iss >> command;

		if (command == "v") { // Vertex
			Vertex vertex;
			float x, y, z;
			iss >> x >> y >> z;
			vertex.position = Vec3(x, y, z);
			vertex.texCoord = float2{0.0f, 0.0f}; // Default texture coordinates
			mesh.addVertex(vertex);
		}
		else if (command == "vt") { // Vertex with texture coordinates
			float2 texCoord;
			iss >> texCoord.x >> texCoord.y;
			mesh.addTextureCoord(texCoord);
		}
		else if (command == "f") { // Face
			std::string vertexParams;
			while (iss >> vertexParams) {
				// Split the vertex parameters by '/'
				std::istringstream vss(vertexParams);
				std::string vertexParam[3];
				while (std::getline(vss, vertexParam[0], '/') && std::getline(vss, vertexParam[1], '/') && std::getline(vss, vertexParam[2], '/')) {
					// Parse the vertex index
					
					unsigned int vertexIndex = std::stoi(vertexParam[0]) - 1; // OBJ indices are 1-based
					mesh.addIndex(vertexIndex);
					// If texture coordinates are present, parse them
					if (!vertexParam[1].empty()) {
						Vertex &vertex = mesh.getVertices()[vertexIndex];
						unsigned int texCoordIndex = std::stoi(vertexParam[1]) - 1;
						vertex.texCoord = mesh.getTexCoord(texCoordIndex);
					}
				}
			}
		}
		else {
			// Ignore other commands (e.g., normals, texture coordinates)
			continue;
		}
	}

	file.close();
	mesh.center();
	return mesh;
}