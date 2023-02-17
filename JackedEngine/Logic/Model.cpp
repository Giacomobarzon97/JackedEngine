#include "Model.h"

Model::Model(std::vector<Vertex> vertices, std::vector<uint16_t> indices) :
vertices(vertices),
indices(indices)
{}

const size_t Model::GetVertexSize() const {
	return sizeof(Vertex);
}

const size_t Model::GetIndexSize() const {
	return sizeof(uint16_t);
}

const size_t Model::GetNumberOfVertices() const {
	return vertices.size();
}

const size_t Model::GetNumberOfIndices() const {
	return indices.size();
}

const void* Model::GetVertexData() const {
	return vertices.data();
}

const void* Model::GetIndexData() const {
	return indices.data();
}