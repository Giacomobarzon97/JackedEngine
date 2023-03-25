#pragma once
#include <string>
#include <vector>
#include "Rendering/Resources/CPUResources/CPUVertices/CPUPositionVertex.h"
#include "Rendering/Resources/CPUResources/CPUVertices/CPUTextureVertex.h"

class CPUModel {
public:
	CPUModel(const std::string objPath);

	const uint32_t GetNumberOfVertices() const;
	const uint32_t GetNumberOfIndices() const;

	const CPUPositionVertex* GetPositionVertexData() const;
	const CPUTextureVertex* GetTextureVertexData() const;
	const uint32_t* GetIndexData() const;

	static const uint32_t GetIndexSize();
	static const VkIndexType GetIndexType();

private:
	std::vector<CPUPositionVertex> positions;
	std::vector<CPUTextureVertex> texCoords;
	std::vector<uint32_t> indices;
};