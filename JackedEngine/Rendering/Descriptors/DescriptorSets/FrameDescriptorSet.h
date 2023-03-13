#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/FrameDescriptorPool.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"

class FrameDescriptorSet : public BaseDescriptorSet{
public:
	FrameDescriptorSet(const Device& device, const FrameDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory);
	FrameDescriptorSet(FrameDescriptorSet&) = delete;
	virtual ~FrameDescriptorSet() override;

	FrameDescriptorSet&operator=(FrameDescriptorSet&) = delete;

	virtual void UpdateDescriptorSet(const glm::mat4 mvpMatrix) const;

private:
	struct UniformBufferObject {
		glm::mat4 mvp;
	};
	const BaseUniformBufferAllocation* const mvpUniform;

};