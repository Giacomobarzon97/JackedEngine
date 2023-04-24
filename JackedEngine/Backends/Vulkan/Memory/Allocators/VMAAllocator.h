#pragma once
#include <vk_mem_alloc.h>
#include "Backends/Vulkan/Memory/Allocators/BaseAllocator.h"

class VMAAllocator : public BaseAllocator{
public:
	VMAAllocator(const Device& device);
	VMAAllocator(VMAAllocator&) = delete;
	~VMAAllocator();
	VMAAllocator& operator=(VMAAllocator&) = delete;

	virtual const VkDeviceSize GetAvailableMemory() const override;

	void CreateBuffer(VkBuffer& buffer, VmaAllocation& allocation, const VkDeviceSize bufferSize, const VkBufferUsageFlags usage, const VkMemoryPropertyFlags properties) const;
	void MapMemory(VmaAllocation& allocation, void*& memLoc) const;
	void UnMapMemory(VmaAllocation& allocation) const;
	void DestroyBuffer(VkBuffer& buffer, VmaAllocation allocation) const;
	void CreateImage(VkImage& image, VmaAllocation& allocation, const uint32_t width, const uint32_t height, const VkFormat format, const VkImageTiling tiling, const VkImageUsageFlags usage, const VkMemoryPropertyFlags properties, const uint32_t arrayLayers, const VkImageCreateFlags flags) const;
	void DestroyImage(VkImage& image, VmaAllocation& allocation) const;

private:
	VmaAllocator allocator;
};