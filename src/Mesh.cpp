#include "Mesh.hpp"

Mesh::Mesh() {
}

Mesh::~Mesh() {
}

void Mesh::addTextureCoord(const float2 &texCoord) {
	this->texCoords.push_back(texCoord);
}

void Mesh::addVertex(const Vertex &vertex) {
	this->vertices.push_back(vertex);
	if (this->vertices.size() == 1) {
		this->min = vertex.position;
		this->max = vertex.position;
	} else {
		this->min = Vec3::min(this->min, vertex.position);
		this->max = Vec3::max(this->max, vertex.position);
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

Vec3 Mesh::getCenter() {
	Vec3 center;
	if (vertices.empty()) {
		return center; // Return zero vector if no vertices are present
	}
	center = (max + min) * 0.5f;
	return center;
}

void Mesh::center() {
	Vec3 center = this->getCenter();
	for (auto &vertex : this->vertices) {
		vertex.position -= center;
	}
	this->min = Vec3();
	this->max = Vec3();
}