#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/ObjectDescriptorPool.h"
#include "Rendering/Resources/GPUResources/GPUImage.h"

class ObjectDescriptorSet : public BaseDescriptorSet{
public:
	ObjectDescriptorSet(const Device& device, const ObjectDescriptorPool& descriptorPool, const GPUImage& imageBuffer);
	ObjectDescriptorSet(ObjectDescriptorSet&) = delete;
	virtual ~ObjectDescriptorSet() override;

	ObjectDescriptorSet& operator=(ObjectDescriptorSet&) = delete;

private:
	const GPUImage& image;
	VkSampler sampler;
};