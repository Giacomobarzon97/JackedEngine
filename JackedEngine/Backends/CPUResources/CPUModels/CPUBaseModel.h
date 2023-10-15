#pragma once
#include <vector>
#include <string>
#include "Backends/CPUResources/CPUVertices/CPUPositionVertex.h"
#include "Backends/CPUResources/CPUVertices/CPUTextureVertex.h"
#include "Backends/CPUResources/CPUVertices/CPUNormalVertex.h"

struct BufferData {
	const void* data;
	uint32_t size;
};

struct ModelData {
	BufferData indexData;
	uint32_t numberOfIndices;
	std::vector<BufferData> vertexData;
};

class CPUBaseModel {
public:
	virtual ~CPUBaseModel();

	virtual void LoadData() = 0;
	virtual const ModelData GetModelData() const = 0;
	virtual const std::string& GetId() const = 0;
};