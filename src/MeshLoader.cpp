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
			vertex.texCoord = float2{{0.0f, 0.0f}}; // Default texture coordinates
			mesh.addVertex(vertex);
		}
		else if (command == "vt") { // Vertex with texture coordinates
			float2 texCoord;
			iss >> texCoord.x >> texCoord.y;
			mesh.addTextureCoord(texCoord);
		}
		else if (command == "f") { // Face
			std::vector<unsigned int> indices;
			std::string vertexParams;
			// TODO: handle non-triangle faces!! (again)
			while (iss >> vertexParams) {
				if (vertexParams.find("/") == std::string::npos) {
					indices.push_back(std::stoi(vertexParams) - 1);
					continue;
				}
				// Split the vertex parameters by '/'
				std::istringstream vss(vertexParams);
				std::string vertexParam[3];
				while (std::getline(vss, vertexParam[0], '/') && std::getline(vss, vertexParam[1], '/') && std::getline(vss, vertexParam[2], '/')) {
					// Parse the vertex index
					unsigned int vertexIndex = std::stoi(vertexParam[0]) - 1; // OBJ indices are 1-based
					indices.push_back(vertexIndex);
					// If texture coordinates are present, parse them
					if (!vertexParam[1].empty()) {
						Vertex &vertex = mesh.getVertices()[vertexIndex];
						unsigned int texCoordIndex = std::stoi(vertexParam[1]) - 1;
						vertex.texCoord = mesh.getTexCoord(texCoordIndex);
					}
				}
			}
			if (indices.size() < 3) {
				throw std::runtime_error("Invalid face index count (< 3)");
			}
			for (size_t i = 2; i < indices.size(); i++) {
				std::cout << "Indices 0 " << i - 1 << " " << i << std::endl;
				mesh.addIndex(indices[0]);
				mesh.addIndex(indices[i - 1]);
				mesh.addIndex(indices[i]);
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