#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "GLContext.hpp"

class Texture {
private:
	GLuint textureID;
	int width, height;
public:
	// data should be in RGBA format
	Texture(const void* data, int width, int height, unsigned int format);
	~Texture();

	void bind(GLuint unit = 0) const;
};

#endif
