#include <iostream>
#include <stdio.h>
#include <chrono>
#include <cmath>
#include "BMPLoader.hpp"
#include "Mat4.hpp"
#include "MeshLoader.hpp"
#include "GLContext.hpp"
#include "ShaderProgram.hpp"

struct final_Vertex {
	float position[2];
	float color[3];
};

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <mesh_file>" << std::endl;
		return -1;
	}
	Mesh mesh = MeshLoader::loadMesh(argv[1]);
	GLContext glContext;
	const Mat4 projectionMatrix(Mat4::perspective(90.0f, 800.0f / 600.0f, 0.1f, 100.0f));
	Mat4 transform;
	Mat4 view = Mat4::lookAt(2.2f, 2.2f, 2.2f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);


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
	Shader vertexShader(GL_VERTEX_SHADER, "assets/shaders/vertex/texture.glsl");
	Shader fragmentShader(GL_FRAGMENT_SHADER, "assets/shaders/fragment/texture.glsl");
	
	ShaderProgram shaderProgram;
	
	shaderProgram.attachShader(vertexShader);
	shaderProgram.attachShader(fragmentShader);
	shaderProgram.link();
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	const std::vector<Vertex> &vertices = mesh.getVertices();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	const std::vector<unsigned int> &elements = mesh.getIndices();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elements.size(), elements.data(), GL_STATIC_DRAW);

	shaderProgram.bindFragDataLocation("outColor", 0);

	GLint position = shaderProgram.getAttributeLocation("position");
	shaderProgram.vertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	GLint transformLocation = shaderProgram.getUniformLocation("transform");
	GLint projectionLocation = shaderProgram.getUniformLocation("projection");
	GLint viewLocation = shaderProgram.getUniformLocation("view");
	//GLint shadeCountLocation = shaderProgram.getUniformLocation("shadeCount");
	
	shaderProgram.link();
	shaderProgram.use();
	//int shadeCounts[3] = { 10, 100, 255 };
	//shaderProgram.setUniform3i(shadeCountLocation, shadeCounts[0], shadeCounts[1], shadeCounts[2]);
	shaderProgram.setUniformMat4(transformLocation, transform);
	shaderProgram.setUniformMat4(projectionLocation, projectionMatrix);
	shaderProgram.setUniformMat4(viewLocation, view);
	
	glEnable(GL_DEPTH_TEST);
	auto t_start = std::chrono::high_resolution_clock::now();
	Window& window = glContext.getWindow();
	while (!window.shouldClose()) {
		if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			window.setShouldClose(true);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		
		transform.setRotation(time * 30.0f, 0.0f, 1.0f, 0.0f);
		shaderProgram.setUniformMat4(transformLocation, transform);
		glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, nullptr);
		window.swapBuffers();
		glContext.pollEvents();
	}
	delete texture;
}
