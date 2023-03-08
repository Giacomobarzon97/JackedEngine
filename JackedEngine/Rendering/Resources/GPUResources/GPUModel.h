#pragma once
#include <string>
#include "Rendering/Data/Model.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"

class GPUModel {
public:
	GPUModel(const BaseAllocationFactory& allocationFactory, const std::string objFilePath);
	GPUModel(GPUModel&) = delete;
	~GPUModel();

	GPUModel& operator=(GPUModel&) = delete;

	const BaseBufferAllocation& GetVertexBufferAllocation() const;
	const BaseBufferAllocation& GetIndexBufferAllocation() const;
	const uint32_t GetNumberOfIndices() const;

private:
	uint32_t nVertices;
	const BaseBufferAllocation* vertexBufferAllocation;
	const BaseBufferAllocation* indexBufferAllocation;
};