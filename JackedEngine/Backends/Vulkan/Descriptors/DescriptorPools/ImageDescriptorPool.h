#pragma once
#include "Backends/Vulkan/Descriptors/DescriptorPools/BaseDescriptorPool.h"

class ImageDescriptorPool : public BaseDescriptorPool{
public:
	ImageDescriptorPool(const Device& device, int maxSets);
	ImageDescriptorPool(ImageDescriptorPool&) = delete;
	virtual ~ImageDescriptorPool() override;

	ImageDescriptorPool& operator=(ImageDescriptorPool&) = delete;
};