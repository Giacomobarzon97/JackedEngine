#pragma once
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/BaseDescriptorLayout.h"

class MaterialDescriptorLayout : public BaseDescriptorLayout{
public:
	MaterialDescriptorLayout(const Device& device);
	MaterialDescriptorLayout(MaterialDescriptorLayout&) = delete;
	MaterialDescriptorLayout& operator=(MaterialDescriptorLayout&) = delete;
};