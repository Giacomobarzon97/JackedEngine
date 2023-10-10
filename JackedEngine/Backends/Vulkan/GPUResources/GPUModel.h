#pragma once
#include <vector>
#include <string>
#include <vulkan/vulkan.h>
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Backends/CPUResources/CPUModels/CPUBaseModel.h"

class GPUModel {
public:
	GPUModel(const BaseAllocationFactory& allocationFactory, const CPUBaseModel& model);
	GPUModel(GPUModel&) = delete;
	~GPUModel();

	GPUModel& operator=(GPUModel&) = delete;

	const std::vector<VkBuffer> GetBuffers() const;
	const BaseIndexBufferAllocation& GetIndexBufferAllocation() const;
	const uint32_t GetNumberOfIndices() const;
	static const VkIndexType GetIndexType();

private:
	uint32_t nVertices;
	std::vector<const BaseVertexBufferAllocation*> bufferAllocations;
	const BaseIndexBufferAllocation* indexBufferAllocation;
};