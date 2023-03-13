#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/ObjectDescriptorPool.h"
#include "Rendering/Resources/GPUResources/GPUImage.h"

class ObjectDescriptorSet : public BaseDescriptorSet{
public:
	ObjectDescriptorSet(const Device& device, const ObjectDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const GPUImage& imageBuffer);
	ObjectDescriptorSet(ObjectDescriptorSet&) = delete;
	virtual ~ObjectDescriptorSet() override;

	ObjectDescriptorSet& operator=(ObjectDescriptorSet&) = delete;

	virtual void UpdateModelMatrix(const glm::mat4 modelMatrix) const;

private:
	struct UniformBufferObject {
		glm::mat4 model;
	};

	const GPUImage& image;
	VkSampler sampler;
	const BaseUniformBufferAllocation* const modelUniform;
};