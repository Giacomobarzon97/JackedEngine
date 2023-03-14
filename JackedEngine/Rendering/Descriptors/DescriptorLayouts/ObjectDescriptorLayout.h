#pragma once
#include "Rendering/Descriptors/DescriptorLayouts/BaseDescriptorLayout.h"

class ObjectDescriptorLayout : public BaseDescriptorLayout{
public:
	ObjectDescriptorLayout(const Device& device);
	ObjectDescriptorLayout(ObjectDescriptorLayout&) = delete;
	ObjectDescriptorLayout& operator=(ObjectDescriptorLayout&) = delete;
};