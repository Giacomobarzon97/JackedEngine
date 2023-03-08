#pragma once
#include "Rendering/Device.h"
#include "Rendering/Memory/Allocations/BaseAllocation.h"

class BaseAllocator {
public:
	BaseAllocator(const Device& device);
	virtual ~BaseAllocator() = 0;

	virtual const VkDeviceSize GetAvailableMemory() const = 0;

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) const;

protected:
	const Device& device;

private:
	VkCommandBuffer beginSingleTimeCommands() const;
	void endSingleTimeCommands(VkCommandBuffer commandBuffer) const;
};