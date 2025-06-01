#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

Shader::Shader(int shaderType, const char* sourcePath) {
	shaderHandle = 0;
	// Load the shader source code from the file
	std::ifstream shaderFile(sourcePath);
	if (!shaderFile) {
		throw std::runtime_error("Failed to open shader file: " + std::string(sourcePath));
	}
	std::string shaderCode((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	// Create the shader object
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) {
		throw std::runtime_error("Failed to create shader of type: " + std::to_string(shaderType));
	}

	// Attach the shader source code and compile it
	const char* shaderSource = shaderCode.c_str();
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		// If compilation failed, retrieve the error log
		// and delete the shader object
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		glDeleteShader(shader);
		throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
	}
	this->shaderHandle = shader;
}

Shader::~Shader() {
	if (this->shaderHandle != 0) {
		glDeleteShader(this->shaderHandle);
		this->shaderHandle = 0;
	}
}

GLuint Shader::getHandle() const {
	return this->shaderHandle;
}