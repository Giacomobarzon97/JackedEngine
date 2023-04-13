#pragma once
#include <vector>
#include <string>
#include <vulkan/vulkan.h>
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Rendering/Resources/CPUResources/CPUModels/CPUBaseModel.h"

class GPUModel {
public:
	GPUModel(const BaseAllocationFactory& allocationFactory, const CPUBaseModel& model);
	GPUModel(GPUModel&) = delete;
	~GPUModel();

	GPUModel& operator=(GPUModel&) = delete;

	const std::vector<VkBuffer> GetBuffers() const;
	const BaseBufferAllocation& GetIndexBufferAllocation() const;
	const uint32_t GetNumberOfIndices() const;
	static const VkIndexType GetIndexType();

private:
	uint32_t nVertices;
	std::vector<const BaseBufferAllocation*> bufferAllocations;
	const BaseBufferAllocation* indexBufferAllocation;
};