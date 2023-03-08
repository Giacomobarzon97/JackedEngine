#pragma once
#include <vk_mem_alloc.h>
#include "Rendering/Memory/Allocators/BaseAllocator.h"

class VMAAllocator : public BaseAllocator{
public:
	VMAAllocator(const Device& device);
	VMAAllocator(VMAAllocator&) = delete;
	~VMAAllocator();
	VMAAllocator& operator=(VMAAllocator&) = delete;

	virtual const VkDeviceSize GetAvailableMemory() const override;
	const VkDeviceSize GetAllocationOffset(const VmaAllocation allocation) const;

	void CreateBuffer(VkBuffer& buffer, VmaAllocation& allocation, const VkDeviceSize bufferSize, const VkBufferUsageFlags usage, const VkMemoryPropertyFlags properties) const;
	void MapMemory(VmaAllocation& allocation, const void* data, const VkDeviceSize dataSize) const;
	void DestroyBuffer(VkBuffer& buffer, VmaAllocation allocation) const;
	

private:
	VmaAllocator allocator;
};