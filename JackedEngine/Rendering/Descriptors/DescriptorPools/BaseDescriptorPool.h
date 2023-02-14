#pragma once
#include "Rendering/Device.h"

class BaseDescriptorPool {
public:
	BaseDescriptorPool(const Device* const device);
	virtual ~BaseDescriptorPool() = 0;

	const VkDescriptorSetLayout* const GetDescriptorSetLayout() const;
	const VkDescriptorPool* const GetDescriptorPool() const;

protected:
	const Device* const device;
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorPool descriptorPool;
};