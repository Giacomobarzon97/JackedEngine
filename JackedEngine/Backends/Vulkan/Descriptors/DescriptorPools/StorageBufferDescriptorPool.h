#pragma once
#include <array>
#include "Backends/Vulkan/Descriptors/DescriptorPools/BaseDescriptorPool.h"

class StorageBufferDescriptorPool : public BaseDescriptorPool{
public:
	StorageBufferDescriptorPool(const Device& device, int maxSets);
	StorageBufferDescriptorPool(StorageBufferDescriptorPool&) = delete;
	virtual ~StorageBufferDescriptorPool() override;

	StorageBufferDescriptorPool&operator=(StorageBufferDescriptorPool&) = delete;

};