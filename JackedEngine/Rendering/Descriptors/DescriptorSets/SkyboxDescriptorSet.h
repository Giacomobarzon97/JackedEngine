#pragma once
#include "Rendering/Samplers/BaseSampler.h"
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorLayouts/SkyboxDescriptorLayout.h"
#include "Rendering/Descriptors/DescriptorPools/SkyboxDescriptorPool.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Rendering/Resources/GPUResources/GPUCubemap.h"

class SkyboxDescriptorSet : public BaseDescriptorSet {
public:
	SkyboxDescriptorSet(const Device& device, const SkyboxDescriptorLayout& descriptorLayout, const SkyboxDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const GPUCubemap& cubemap, const BaseSampler& sampler);
	SkyboxDescriptorSet(SkyboxDescriptorSet&) = delete;
	virtual ~SkyboxDescriptorSet() override;

	SkyboxDescriptorSet& operator=(SkyboxDescriptorSet&) = delete;

private:
	const GPUCubemap& cubemap;
	const BaseSampler& sampler;
};