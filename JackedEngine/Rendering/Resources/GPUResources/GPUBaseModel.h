#pragma once
#include "Rendering/Resources/CPUResources/CPUModel.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"

class GPUBaseModel {
public:
	GPUBaseModel(const BaseAllocationFactory& allocationFactory, const CPUModel& model);
	GPUBaseModel(GPUBaseModel&) = delete;
	~GPUBaseModel();

	GPUBaseModel& operator=(GPUBaseModel&) = delete;

	const BaseVertexBufferAllocation& GetPositionsBufferAllocation() const;
	const BaseIndexBufferAllocation& GetIndexBufferAllocation() const;
	const uint32_t GetNumberOfIndices() const;

private:
	uint32_t nVertices;
	const BaseVertexBufferAllocation* positionsBufferAllocation;
	const BaseIndexBufferAllocation* indexBufferAllocation;
};