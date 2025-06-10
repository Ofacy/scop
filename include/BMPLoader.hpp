#ifndef BMPLOADER_HPP
#define BMPLOADER_HPP

# include "Texture.hpp"

class BMPLoader {
public:
	static Texture *loadBMP(const char *filename);
};

#endif
