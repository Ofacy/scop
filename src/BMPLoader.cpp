#include "BMPLoader.hpp"
#include <iostream>
#include <fstream>

Texture *BMPLoader::loadBMP(const char *filename) {

	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		return nullptr; // File could not be opened
	}

	// Read BMP header
	char header[54];
	file.read(header, 54);
	if (file.gcount() != 54 || header[0] != 'B' || header[1] != 'M') {
		return nullptr; // Not a valid BMP file
	}
	int width = *reinterpret_cast<int*>(&header[18]);
	int height = *reinterpret_cast<int*>(&header[22]);
	int dataOffset = *reinterpret_cast<int*>(&header[10]);
	if (width <= 0 || height <= 0 || dataOffset < 54) {
		return nullptr; // Invalid dimensions or data offset
	}
	int bpp = *reinterpret_cast<short*>(&header[28]);
	if (bpp != 24 && bpp != 32) {
		return nullptr; // Only support 24-bit or 32-bit BMP files
	}
	// Calculate the size of the pixel data
	int pixelDataSize = width * height * (bpp / 8);
	char *pixelData = new char[pixelDataSize];
	file.seekg(dataOffset, std::ios::beg);
	file.read(pixelData, pixelDataSize);
	if (file.gcount() != pixelDataSize) {
		delete[] pixelData; // Clean up if read failed
		return nullptr; // Could not read pixel data
	}
	Texture *texture = new Texture(pixelData, width, height, bpp == 32 ? GL_BGRA : GL_BGR);
	delete[] pixelData; // Clean up pixel data after creating texture
	file.close();
	return texture;
}