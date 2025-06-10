#include "Texture.hpp"
#include <stdexcept>

Texture::Texture(const void *data, int width, int height, unsigned int format) {
	glGenTextures(1, &this->textureID);
	if (!this->textureID) {
		throw std::runtime_error("Failed to generate texture ID");
	}
	this->width = width;
	this->height = height;
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture() {
	if (textureID) {
		glDeleteTextures(1, &textureID);
	}
}
