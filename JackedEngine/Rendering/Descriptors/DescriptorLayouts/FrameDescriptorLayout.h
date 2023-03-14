#pragma once
#include "Rendering/Descriptors/DescriptorLayouts/BaseDescriptorLayout.h"

class FrameDescriptorLayout : public BaseDescriptorLayout {
public:
	FrameDescriptorLayout(const Device& device);
	FrameDescriptorLayout(FrameDescriptorLayout&) = delete;
	FrameDescriptorLayout& operator=(FrameDescriptorLayout&) = delete;
};