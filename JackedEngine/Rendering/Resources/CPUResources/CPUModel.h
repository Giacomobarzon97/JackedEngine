#pragma once
#include <string>
#include <vector>
#include "Rendering/Resources/CPUResources/CPUVertex.h"

class CPUModel {
public:
	CPUModel(const std::string objPath);

	const size_t GetVertexSize() const;
	const size_t GetIndexSize() const;
	const uint32_t GetNumberOfVertices() const;
	const uint32_t GetNumberOfIndices() const;
	const void* GetVertexData() const;
	const void* GetIndexData() const;
	static const VkIndexType GetIndexType();

private:
	std::vector<CPUVertex> vertices;
	std::vector<uint32_t> indices;
};