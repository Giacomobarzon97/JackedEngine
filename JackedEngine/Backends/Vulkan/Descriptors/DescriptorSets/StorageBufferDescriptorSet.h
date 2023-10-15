#pragma once
#include "Backends/Vulkan/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/StorageBufferDescriptorLayout.h"
#include "Backends/Vulkan/Descriptors/DescriptorPools/StorageBufferDescriptorPool.h"
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"

class StorageBufferDescriptorSet : public BaseDescriptorSet{
public:
	StorageBufferDescriptorSet(const Device& device, const StorageBufferDescriptorLayout& descriptorLayout, const StorageBufferDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const uint32_t elementSize, const uint32_t maxElements);
	StorageBufferDescriptorSet(StorageBufferDescriptorSet&) = delete;
	virtual ~StorageBufferDescriptorSet() override;

	StorageBufferDescriptorSet&operator=(StorageBufferDescriptorSet&) = delete;

	virtual void UpdateBuffer(const void * data, const uint32_t nElements) const;

private:
	const BaseStorageBufferAllocation* const storageBufferAllocation;
};