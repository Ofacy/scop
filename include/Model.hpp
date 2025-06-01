#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>


typedef struct {
	float x, y, z;
} float3;

typedef float3 Vertex;

class Model {
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	float3 max;
	float3 min;
public:
	Model();
	~Model();

	void addVertex(float x, float y, float z);
	void addIndex(unsigned int index);
	std::vector<Vertex> getVertices() const;
	std::vector<unsigned int> getIndices() const;
	float3 getCenter();
	void center();
};

#endif