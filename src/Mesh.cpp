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

std::vector<Vertex> &Mesh::getVertices() {
	return vertices;
}

std::vector<unsigned int> &Mesh::getIndices() {
	return indices;
}

const float2& Mesh::getTexCoord(unsigned int index) const {
	if (index < texCoords.size()) {
		return texCoords[index];
	}
	throw std::out_of_range("Texture coordinate index out of range");
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
	this->min -= center;
	this->max -= center;
	float2 scaling = {{
		0.5f / (this->max.getZ() == 0 ? 1 : this->max.getZ()),
		0.5f / (this->max.getY() == 0 ? 1 : this->max.getY())
	}};
	float2 offset = {{
		0.5,
		0.5
	}};
	for (auto &vertex : this->vertices) {
		vertex.position -= center;
		if (texCoords.empty()) {
			vertex.texCoord = {{
				vertex.position.getZ() * scaling.x + offset.x,
				vertex.position.getY() * scaling.y + offset.y
			}};
		}
	}
}


std::ostream &operator<<(std::ostream &stream, const float2 &values) {
	stream << "(" << values.x << ", " << values.y << ")";
	return stream;
}
