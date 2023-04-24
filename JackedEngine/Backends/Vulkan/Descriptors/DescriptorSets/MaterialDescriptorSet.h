#pragma once
#include "Backends/Vulkan/Samplers/BaseSampler.h"
#include "Backends/Vulkan/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Backends/Vulkan/Descriptors/DescriptorPools/MaterialDescriptorPool.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/MaterialDescriptorLayout.h"
#include "Backends/Vulkan/GPUResources/GPUImage.h"

class MaterialDescriptorSet : public BaseDescriptorSet{
public:
	MaterialDescriptorSet(const Device& device, const MaterialDescriptorLayout& descriptorLayout,const MaterialDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const GPUImage& imageBuffer, const BaseSampler& sampler);
	MaterialDescriptorSet(MaterialDescriptorSet&) = delete;
	virtual ~MaterialDescriptorSet() override;

	MaterialDescriptorSet& operator=(MaterialDescriptorSet&) = delete;

private:
	const GPUImage& image;
	const BaseSampler& sampler;
};