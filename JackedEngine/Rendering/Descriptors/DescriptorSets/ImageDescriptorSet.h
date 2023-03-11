#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/ImageDescriptorPool.h"
#include "Rendering/Resources/GPUResources/GPUImage.h"

class ImageDescriptorSet : public BaseDescriptorSet{
public:
	ImageDescriptorSet(const Device& device, const ImageDescriptorPool& descriptorPool, const GPUImage& imageBuffer);
	ImageDescriptorSet(ImageDescriptorSet&) = delete;
	virtual ~ImageDescriptorSet() override;

	ImageDescriptorSet& operator=(ImageDescriptorSet&) = delete;

private:
	const GPUImage& image;
	VkSampler sampler;
};