#pragma once
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/BaseDescriptorLayout.h"

class StorageBufferDescriptorLayout : public BaseDescriptorLayout {
public:
	StorageBufferDescriptorLayout(const Device& device);
	StorageBufferDescriptorLayout(StorageBufferDescriptorLayout&) = delete;
	StorageBufferDescriptorLayout& operator=(StorageBufferDescriptorLayout&) = delete;
};