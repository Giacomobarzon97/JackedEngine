#pragma once
#include "Backends/Vulkan/Samplers/BaseSampler.h"
#include "Backends/Vulkan/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Backends/Vulkan/Descriptors/DescriptorPools/ImageDescriptorPool.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/ImageDescriptorLayout.h"
#include "Backends/Vulkan/GPUResources/GPUImage.h"

class ImageDescriptorSet : public BaseDescriptorSet{
public:
	ImageDescriptorSet(const Device& device, const ImageDescriptorLayout& descriptorLayout,const ImageDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const GPUImage& imageBuffer, const BaseSampler& sampler);
	ImageDescriptorSet(ImageDescriptorSet&) = delete;
	virtual ~ImageDescriptorSet() override;

	ImageDescriptorSet& operator=(ImageDescriptorSet&) = delete;

private:
	const GPUImage& image;
	const BaseSampler& sampler;
};