#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/BufferAllocations/CubemapBufferAllocations/BaseCubemapBufferAllocation.h"

class VMACubemapBufferAllocation : public BaseCubemapBufferAllocation {
public:
	VMACubemapBufferAllocation(const VMAAllocator& allocator, const void* frontFaceData, const void* backFaceData, const void* upFaceData, const void* downFaceData, const void* rightFaceData, const void* leftFaceData, const int width, const int height);
	VMACubemapBufferAllocation(VMACubemapBufferAllocation&) = delete;
	~VMACubemapBufferAllocation();
	VMACubemapBufferAllocation& operator=(VMACubemapBufferAllocation&) = delete;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
};