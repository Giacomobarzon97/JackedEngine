#pragma once
#include "Rendering/Samplers/BaseSampler.h"
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/MaterialDescriptorPool.h"
#include "Rendering/Descriptors/DescriptorLayouts/MaterialDescriptorLayout.h"
#include "Rendering/Resources/GPUResources/GPUImage.h"

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