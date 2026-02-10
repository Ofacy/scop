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
	unsigned char rgb[3] = {255, 130, 34};

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " [-t <texture_path.bmp>] [-s <r> <g> <b>] <mesh_file>" << std::endl;
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
		else if (arg == "-s") {
			for (unsigned char i = 0;i < 3; i++) {
				const char *str = *(++argv);
				if (!str) {
					std::cerr << "Missing values for parameter '-s'" << std::endl;
					return 1;
				}
				rgb[i] = std::atoi(str);
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
		std::cerr << "OBJ file required!" << std::endl;
		return 1;
	}
	Texture *texture = nullptr;
	try {
		Mesh mesh = MeshLoader::loadMesh(mesh_path);
		GLContext &glContext = GLContext::getInstance();
		glContext.init();
		if (texture_path) {
			texture = BMPLoader::loadBMP(texture_path);
			if (!texture) {
				std::cerr << "Failed to load texture " << texture_path << std::endl;
				return -1;
			}
			else {
				texture->bind();
			}
		}
		glEnable(GL_DEPTH_TEST);
		Scop scop(mesh, texture, rgb);
		scop.start();
	}
	catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	delete texture;
}
