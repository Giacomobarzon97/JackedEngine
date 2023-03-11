#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/BufferAllocations/ImageBufferAllocations/BaseImageBufferAllocation.h"

class VMAImageBufferAllocation : public BaseImageBufferAllocation {
public:
	VMAImageBufferAllocation(const VMAAllocator& allocator, const void* data, const int width, const int height);
	VMAImageBufferAllocation(VMAImageBufferAllocation&) = delete;
	~VMAImageBufferAllocation();
	VMAImageBufferAllocation& operator=(VMAImageBufferAllocation&) = delete;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;

	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
};