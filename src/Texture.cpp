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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
	if (textureID) {
		glDeleteTextures(1, &textureID);
	}
}

void Texture::bind(GLuint unit) const {
	if (unit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
		throw std::runtime_error("Texture unit exceeds maximum combined texture image units");
	}
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}
