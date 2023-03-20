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
};