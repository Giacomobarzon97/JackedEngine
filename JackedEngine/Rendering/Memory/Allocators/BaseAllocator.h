#pragma once
#include "Rendering/Device.h"

class BaseAllocator {
public:
	BaseAllocator(const Device& device);
	virtual ~BaseAllocator() = 0;

	virtual const VkDeviceSize GetAvailableMemory() const = 0;

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) const;
	VkCommandBuffer beginSingleTimeCommands() const;
	void endSingleTimeCommands(VkCommandBuffer commandBuffer) const;
	
	const Device& GetDevice() const;

protected:
	const Device& device;
};