#include "ModelLoader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

Model ModelLoader::loadModel(const std::string& filePath) {
	Model model;

	// Open the file
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open model file: " + filePath);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string command;
		iss >> command;

		if (command == "v") { // Vertex
			float x, y, z;
			iss >> x >> y >> z;
			model.addVertex(x, y, z);
		} else if (command == "f") { // Face
			unsigned int index;
			size_t numIndices = 0;
			unsigned int lastIndex = 0;
			unsigned int firstIndex = 0;
			while (iss >> index) {
				index--;
				if (numIndices == 0) {
					firstIndex = index; // OBJ indices are 1-based
				} else if (numIndices == 1) {
					lastIndex = index; // Store the second index
				} else {
					model.addIndex(firstIndex);
					model.addIndex(lastIndex);
					model.addIndex(index); // Add the third index
					lastIndex = index; // Update last index for next iteration
				}
				numIndices++;
			}
		}
		else
		{
			// Ignore other commands (e.g., normals, texture coordinates)
			continue;
		}
	}

	file.close();
	model.center();
	return model;
}