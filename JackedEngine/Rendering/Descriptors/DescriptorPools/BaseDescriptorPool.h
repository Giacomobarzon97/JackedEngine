#pragma once
#include "Rendering/Device.h"

class BaseDescriptorPool {
public:
	BaseDescriptorPool(const Device& device);
	virtual ~BaseDescriptorPool() = 0;

	const VkDescriptorPool& GetDescriptorPool() const;

protected:
	const Device& device;
	VkDescriptorPool descriptorPool;
};