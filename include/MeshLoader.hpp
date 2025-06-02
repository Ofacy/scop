#ifndef MESHLOADER_HPP
#define MESHLOADER_HPP

#include "Mesh.hpp"
#include <string>

class MeshLoader {
public:
	static Mesh loadMesh(const std::string& filePath);

};

#endif