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

	const BaseVertexBufferAllocation& GetVertexBufferAllocation() const;
	const BaseIndexBufferAllocation& GetIndexBufferAllocation() const;
	const uint32_t GetNumberOfIndices() const;

private:
	uint32_t nVertices;
	const BaseVertexBufferAllocation* vertexBufferAllocation;
	const BaseIndexBufferAllocation* indexBufferAllocation;
};