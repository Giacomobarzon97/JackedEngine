#pragma once
#include "Rendering/Device.h"

class BaseDescriptorLayout {
public:
	BaseDescriptorLayout(const Device& device);
	virtual ~BaseDescriptorLayout() = 0;

	const VkDescriptorSetLayout& GetDescriptorLayout() const;

protected:
	const Device& device;
	VkDescriptorSetLayout descriptorSetLayout;
};