#ifndef SHADER_HPP
#define SHADER_HPP

#include "GLContext.hpp"

class Shader {
private:
	GLuint shaderHandle;
public:
	Shader(int shaderType, const char* sourcePath);
	~Shader();
	
	void bufferData(const void* data, GLsizeiptr size, GLenum usage) const;
	GLuint getHandle() const;

};


#endif