#include "ShaderProgram.hpp"
#include <stdexcept>

ShaderProgram::ShaderProgram() {
	programHandle = glCreateProgram();
	if (programHandle == 0) {
		throw std::runtime_error("Failed to create shader program");
	}
}

ShaderProgram::~ShaderProgram() {
	if (programHandle != 0) {
		glDeleteProgram(programHandle);
		programHandle = 0;
	}
}

void ShaderProgram::attachShader(const Shader& shader) {
	glAttachShader(programHandle, shader.getHandle());
}

void ShaderProgram::link() {
	glLinkProgram(programHandle);

	GLint success;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(programHandle, sizeof(infoLog), nullptr, infoLog);
		throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
	}
}

void ShaderProgram::use() const {
	glUseProgram(programHandle);
}

void ShaderProgram::bindFragDataLocation(const char* name, GLuint colorAttachment) {
	glBindFragDataLocation(programHandle, colorAttachment, name);
}

GLint ShaderProgram::getAttributeLocation(const char* name) const {
	return glGetAttribLocation(programHandle, name);
}

GLint ShaderProgram::getUniformLocation(const char* name) const {
	GLint location = glGetUniformLocation(programHandle, name);
	if (location == -1) {
		throw std::runtime_error("Uniform not found: " + std::string(name));
	}
	return location;
}

void ShaderProgram::setUniform1f(GLint location, float value) const {
	glUniform1f(location, value);
}

void ShaderProgram::setUniform1u(GLint location, unsigned int value) const {
	glUniform1ui(location, value);
}

void ShaderProgram::setUniform1i(GLint location, int value) const {
	glUniform1i(location, value);
}

void ShaderProgram::setUniform2i(GLint location, int v0, int v1) const {
	glUniform2i(location, v0, v1);
}

void ShaderProgram::setUniform3f(GLint location, float v0, float v1, float v2) const {
	glUniform3f(location, v0, v1, v2);
}

void ShaderProgram::setUniform3i(GLint location, int v0, int v1, int v2) const {
	glUniform3i(location, v0, v1, v2);
}

void ShaderProgram::setUniform3u(GLint location, unsigned int v0, unsigned int v1, unsigned int v2) const {
	glUniform3ui(location, v0, v1, v2);
}

void ShaderProgram::setUniformMat4(GLint location, const Mat4 &matrix) const {
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix.data());
}

void ShaderProgram::enableVertexAttribArray(GLint index) const {
	glEnableVertexAttribArray(index);
	if (glGetError() != GL_NO_ERROR) {
		throw std::runtime_error("Failed to enable vertex attribute array at index: " + std::to_string(index));
	}
}

void ShaderProgram::vertexAttribPointer(GLint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) const {
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}
