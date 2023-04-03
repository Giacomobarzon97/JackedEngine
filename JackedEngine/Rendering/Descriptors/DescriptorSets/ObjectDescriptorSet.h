#pragma once
#include "Rendering/Samplers/BaseSampler.h"
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/ObjectDescriptorPool.h"
#include "Rendering/Descriptors/DescriptorLayouts/ObjectDescriptorLayout.h"
#include "Rendering/Resources/GPUResources/GPUImage.h"

class ObjectDescriptorSet : public BaseDescriptorSet{
public:
	ObjectDescriptorSet(const Device& device, const ObjectDescriptorLayout& descriptorLayout,const ObjectDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const GPUImage& imageBuffer, const BaseSampler& sampler);
	ObjectDescriptorSet(ObjectDescriptorSet&) = delete;
	virtual ~ObjectDescriptorSet() override;

	ObjectDescriptorSet& operator=(ObjectDescriptorSet&) = delete;

private:
	const GPUImage& image;
	const BaseSampler& sampler;
};