#include "Mesh.hpp"

Mesh::Mesh() {
}

Mesh::~Mesh() {
}

void Mesh::addVertex(float x, float y, float z) {
	vertices.push_back({x, y, z});
	if (vertices.size() == 1) {
		min = {x, y, z};
		max = {x, y, z};
	} else {
		min.x = std::min(min.x, x);
		min.y = std::min(min.y, y);
		min.z = std::min(min.z, z);
		max.x = std::max(max.x, x);
		max.y = std::max(max.y, y);
		max.z = std::max(max.z, z);
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
	center.x = (min.x + max.x) / 2.0f;
	center.y = (min.y + max.y) / 2.0f;
	center.z = (min.z + max.z) / 2.0f;
	return center;
}

void Mesh::center() {
	float3 center = getCenter();
	for (auto &vertex : vertices) {
		vertex.x -= center.x;
		vertex.y -= center.y;
		vertex.z -= center.z;
	}
	min = {0.0f, 0.0f, 0.0f};
	max = {0.0f, 0.0f, 0.0f};
}