#include <iostream>
#include <stdio.h>
#include <chrono>
#include <cmath>
#include "BMPLoader.hpp"
#include "Mat4.hpp"
#include "MeshLoader.hpp"
#include "GLContext.hpp"
#include "ShaderProgram.hpp"
#include "Scop.hpp"

int main(int argc, char** argv)
{
	char	*mesh_path = NULL;
	char	*texture_path = NULL;

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " [-t <texture_path.bmp>] <mesh_file>" << std::endl;
		return -1;
	}
	while (*(++argv)) {
		std::string arg = *argv;
		if (arg == "-t") {
			texture_path = *(++argv);
			if (texture_path == nullptr) {
				std::cerr << "Invalid -t usage!" << std::endl;
				return 1;
			}
		}
		else {
			if (mesh_path) {
				std::cerr << "Cannot specify more than one OBJ file!" << std::endl;
				return 1;
			}
			mesh_path = *argv;
		}
	}
	if (!mesh_path) {
		std::cerr << "OBJ file needed!" << std::endl;
		return 1;
	}
	Mesh mesh = MeshLoader::loadMesh(mesh_path);
	GLContext &glContext = GLContext::getInstance();
	try {
		glContext.init();
	} catch (const std::runtime_error& e) {
		std::cerr << "Runtime error: " << e.what() << std::endl;
		return -1;
	}
	Texture *texture = nullptr;
	if (texture_path) {
		texture = BMPLoader::loadBMP(texture_path);
		if (!texture) {
			std::cerr << "Failed to load texture." << std::endl;
			return -1;
		}
		else {
			glActiveTexture(GL_TEXTURE0);
			texture->bind();
		}
	}
	glEnable(GL_DEPTH_TEST);
	Scop scop(mesh, texture ? true : false);
	scop.start();
	delete texture;
}
