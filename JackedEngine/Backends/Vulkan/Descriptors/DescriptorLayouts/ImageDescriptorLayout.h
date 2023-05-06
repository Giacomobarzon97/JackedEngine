#pragma once
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/BaseDescriptorLayout.h"

class ImageDescriptorLayout : public BaseDescriptorLayout{
public:
	ImageDescriptorLayout(const Device& device);
	ImageDescriptorLayout(ImageDescriptorLayout&) = delete;
	ImageDescriptorLayout& operator=(ImageDescriptorLayout&) = delete;
};