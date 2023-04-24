#pragma once
#include "Backends/Vulkan/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/FrameDescriptorLayout.h"
#include "Backends/Vulkan/Descriptors/DescriptorPools/FrameDescriptorPool.h"
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"

class FrameDescriptorSet : public BaseDescriptorSet{
public:
	FrameDescriptorSet(const Device& device, const FrameDescriptorLayout& descriptorLayout, const FrameDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory);
	FrameDescriptorSet(FrameDescriptorSet&) = delete;
	virtual ~FrameDescriptorSet() override;

	FrameDescriptorSet&operator=(FrameDescriptorSet&) = delete;

	virtual void UpdateUBO(const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix) const;

private:
	struct UniformBufferObject {
		alignas(16) glm::mat4 viewMatrix;
		alignas(16) glm::mat4 projectionMatrix;
	};
	const BaseUniformAllocation* const projectionViewUniform;
};