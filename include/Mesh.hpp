#ifndef MESH_HPP
#define MESH_HPP

#include "Vec3.hpp"
#include <vector>
#include "GLContext.hpp"


typedef union {
	struct {
		float x, y;
	};
	float data[2];
} float2;

typedef struct s_vertex {
	Vec3	position;
	float2	texCoord;
} Vertex;

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<float2> texCoords;
	std::vector<unsigned int> indices;

	Vec3 max;
	Vec3 min;
public:
	Mesh();
	~Mesh();

	void addTextureCoord(const float2 &texCoord);
	void addVertex(const Vertex &vertex);
	void addIndex(unsigned int index);
	std::vector<Vertex> &getVertices();
	std::vector<unsigned int> &getIndices();
	const float2& getTexCoord(unsigned int index) const;
	Vec3 getCenter();
	void center();
	
};

#endif