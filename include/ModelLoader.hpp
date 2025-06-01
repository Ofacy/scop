#ifndef MODELLOADER_HPP
#define MODELLOADER_HPP

#include "Model.hpp"
#include <string>

class ModelLoader {
public:
	static Model loadModel(const std::string& filePath);

};

#endif