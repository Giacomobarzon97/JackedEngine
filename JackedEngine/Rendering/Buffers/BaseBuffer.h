#pragma once
#include "Rendering/Device.h"

class BaseBuffer {
public:
	BaseBuffer(const Device& device);
	virtual ~BaseBuffer() = 0;

protected:
	const Device& device;

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
};