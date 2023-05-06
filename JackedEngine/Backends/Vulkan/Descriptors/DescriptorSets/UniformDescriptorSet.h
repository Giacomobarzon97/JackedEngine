#pragma once
#include "Backends/Vulkan/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/UniformDescriptorLayout.h"
#include "Backends/Vulkan/Descriptors/DescriptorPools/UniformDescriptorPool.h"
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"

class UniformDescriptorSet : public BaseDescriptorSet{
public:
	UniformDescriptorSet(const Device& device, const UniformDescriptorLayout& descriptorLayout, const UniformDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const uint32_t uniformSize);
	UniformDescriptorSet(UniformDescriptorSet&) = delete;
	virtual ~UniformDescriptorSet() override;

	UniformDescriptorSet&operator=(UniformDescriptorSet&) = delete;

	virtual void UpdateUniform(const void * data) const;

private:
	const BaseUniformAllocation* const uniformAllocation;
};