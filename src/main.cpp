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

struct final_Vertex {
	float position[2];
	float color[3];
};

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <mesh_file> [-t <texture_path.bmp>]" << std::endl;
		return -1;
	}
	Mesh mesh = MeshLoader::loadMesh(argv[1]);
	GLContext &glContext = GLContext::getInstance();
	try {
		glContext.init();
	} catch (const std::runtime_error& e) {
		std::cerr << "Runtime error: " << e.what() << std::endl;
		return -1;
	}
	Texture *texture = BMPLoader::loadBMP("assets/textures/qpupier.bmp");
	if (!texture) {
		std::cerr << "Failed to load texture." << std::endl;
		return -1;
	}
	else {
		glActiveTexture(GL_TEXTURE0);
		texture->bind();
		glEnable(GL_DEPTH_TEST);
	}
	Scop scop(mesh, texture ? true : false);
	scop.start();
	delete texture;
}
