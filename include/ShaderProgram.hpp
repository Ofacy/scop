#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "Shader.hpp"
#include "Mat4.hpp"

class ShaderProgram {
private:
	GLuint programHandle;
public:
	ShaderProgram();
	~ShaderProgram();

	void attachShader(const Shader& shader);
	void link();
	void use() const;

	void bindFragDataLocation(const char* name, GLuint colorAttachment);
	GLint getAttributeLocation(const char* name) const;
	GLint getUniformLocation(const char* name) const;

	void setUniform1f(GLint location, float value) const;
	void setUniform1u(GLint location, unsigned int value) const;
	void setUniform1i(GLint location, int value) const;

	void setUniform3f(GLint location, float v0, float v1, float v2) const;
	void setUniform3i(GLint location, int v0, int v1, int v2) const;
	void setUniform3u(GLint location, unsigned int v0, unsigned int v1, unsigned int v2) const;

	void setUniformMat4(GLint location, const Mat4 &matrix) const;

	void enableVertexAttribArray(GLint index) const;
	void vertexAttribPointer(GLint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const;

	GLuint getHandle() const;
};

#endif