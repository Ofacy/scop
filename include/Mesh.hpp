#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "GLContext.hpp"

typedef struct {
	float x, y, z;
} float3;

typedef float3 Vertex;

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	float3 max;
	float3 min;
public:
	Mesh();
	~Mesh();

	void addVertex(float x, float y, float z);
	void addIndex(unsigned int index);
	std::vector<Vertex> getVertices() const;
	std::vector<unsigned int> getIndices() const;
	float3 getCenter();
	void center();
	
};

#endif