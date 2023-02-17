#pragma once
#include <vector>
#include "Logic/Vertex.h"

class Model {
public:
	Model(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
	const size_t GetVertexSize() const;
	const size_t GetIndexSize() const;
	const size_t GetNumberOfVertices() const;
	const size_t GetNumberOfIndices() const;
	const void* GetVertexData() const;
	const void* GetIndexData() const;

private:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};