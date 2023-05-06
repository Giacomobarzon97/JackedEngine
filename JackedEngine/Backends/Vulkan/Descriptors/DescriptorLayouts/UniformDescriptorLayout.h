#pragma once
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/BaseDescriptorLayout.h"

class UniformDescriptorLayout : public BaseDescriptorLayout {
public:
	UniformDescriptorLayout(const Device& device);
	UniformDescriptorLayout(UniformDescriptorLayout&) = delete;
	UniformDescriptorLayout& operator=(UniformDescriptorLayout&) = delete;
};