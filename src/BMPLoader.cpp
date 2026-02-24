#include "BMPLoader.hpp"
#include <iostream>
#include <fstream>

# define BMP_OFFSET_IDENTIFIER0 0
# define BMP_OFFSET_IDENTIFIER1 1
# define BMP_OFFSET_WIDTH 18
# define BMP_OFFSET_HEIGHT 22
# define BMP_OFFSET_DATA_OFFSET 10
# define BMP_OFFSET_BPP 28
# define BMP_HEADER_SIZE 54

Texture *BMPLoader::loadBMP(const char *filename) {

	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		return nullptr; // File could not be opened
	}

	// Read BMP header
	char header[BMP_HEADER_SIZE];
	file.read(header, sizeof(header));
	if (file.gcount() != sizeof(header) || header[BMP_OFFSET_IDENTIFIER0] != 'B' || header[BMP_OFFSET_IDENTIFIER1] != 'M') {
		return nullptr; // Not a valid BMP file
	}
	int width = *reinterpret_cast<int*>(&header[BMP_OFFSET_WIDTH]);
	int height = *reinterpret_cast<int*>(&header[BMP_OFFSET_HEIGHT]);
	int dataOffset = *reinterpret_cast<int*>(&header[BMP_OFFSET_DATA_OFFSET]);
	if (width <= 0 || height <= 0 || dataOffset < BMP_HEADER_SIZE) {
		return nullptr; // Invalid dimensions or data offset
	}
	int bpp = *reinterpret_cast<short*>(&header[BMP_OFFSET_BPP]);
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