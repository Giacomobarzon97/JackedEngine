#pragma once
#include "Rendering/Device.h"

class BaseAllocator {
public:
	BaseAllocator(const Device& device);
	virtual ~BaseAllocator() = 0;

	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) const;
	void TransitionImageLayout(const VkImage& image, const VkFormat& format, const VkImageLayout& oldLayout, const VkImageLayout& newLayout, const uint32_t layerCount) const;
	void CopyBufferToImage(const VkBuffer& buffer, const VkImage& image, const uint32_t width, const uint32_t height, const uint32_t layerCount) const;

	const Device& GetDevice() const;
	virtual const VkDeviceSize GetAvailableMemory() const = 0;

protected:
	const Device& device;

private:
	VkCommandBuffer beginSingleTimeCommands() const;
	void endSingleTimeCommands(VkCommandBuffer commandBuffer) const;

};