#include "Mesh.hpp"

Mesh::Mesh() {
}

Mesh::~Mesh() {
}

void Mesh::addVertex(float x, float y, float z) {
	this->vertices.push_back({x, y, z});
	if (this->vertices.size() == 1) {
		this->min = {x, y, z};
		this->max = {x, y, z};
	} else {
		this->min.x = std::min(this->min.x, x);
		this->min.y = std::min(this->min.y, y);
		this->min.z = std::min(this->min.z, z);
		this->max.x = std::max(this->max.x, x);
		this->max.y = std::max(this->max.y, y);
		this->max.z = std::max(this->max.z, z);
	}
}

void Mesh::addIndex(unsigned int index) {
	indices.push_back(index);
}

std::vector<Vertex> Mesh::getVertices() const {
	return vertices;
}

std::vector<unsigned int> Mesh::getIndices() const {
	return indices;
}

float3 Mesh::getCenter() {
	float3 center;
	center.x = (this->min.x + this->max.x) / 2.0f;
	center.y = (this->min.y + this->max.y) / 2.0f;
	center.z = (this->min.z + this->max.z) / 2.0f;
	return center;
}

void Mesh::center() {
	float3 center = this->getCenter();
	for (auto &vertex : this->vertices) {
		vertex.x -= center.x;
		vertex.y -= center.y;
		vertex.z -= center.z;
	}
	this->min = {0.0f, 0.0f, 0.0f};
	this->max = {0.0f, 0.0f, 0.0f};
}