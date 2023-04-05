#pragma once
#include <vector>
#include <string>
#include <vulkan/vulkan.h>
#include "Rendering/Resources/CPUResources/CPUVertices/CPUPositionVertex.h"
#include "Rendering/Resources/CPUResources/CPUVertices/CPUTextureVertex.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"

class GPUModel {
public:
	GPUModel(const BaseAllocationFactory& allocationFactory, const std::vector<uint32_t>& indices, const std::vector<CPUPositionVertex>& positions);
	GPUModel(const BaseAllocationFactory& allocationFactory, const std::vector<uint32_t>& indices, const std::vector<CPUTextureVertex>& texCoords);
	GPUModel(const BaseAllocationFactory& allocationFactory, const std::vector<uint32_t>& indices, const std::vector<CPUPositionVertex>& positions, const std::vector<CPUTextureVertex>& texCoords);
	GPUModel(const BaseAllocationFactory& allocationFactory, const std::string objPath);
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