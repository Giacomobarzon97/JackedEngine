#pragma once
#include "Rendering/Device.h"

class BaseDescriptorPool {
public:
	BaseDescriptorPool(const Device& device);
	virtual ~BaseDescriptorPool() = 0;

	const VkDescriptorSetLayout& GetDescriptorSetLayout() const;
	const VkDescriptorPool& GetDescriptorPool() const;

protected:
	const Device& device;
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorPool descriptorPool;
};