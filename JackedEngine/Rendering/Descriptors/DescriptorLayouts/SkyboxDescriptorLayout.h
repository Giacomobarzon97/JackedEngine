#pragma once
#include "Rendering/Descriptors/DescriptorLayouts/BaseDescriptorLayout.h"

class SkyboxDescriptorLayout : public BaseDescriptorLayout {
public:
	SkyboxDescriptorLayout(const Device& device);
	SkyboxDescriptorLayout(SkyboxDescriptorLayout&) = delete;
	SkyboxDescriptorLayout& operator=(SkyboxDescriptorLayout&) = delete;
};