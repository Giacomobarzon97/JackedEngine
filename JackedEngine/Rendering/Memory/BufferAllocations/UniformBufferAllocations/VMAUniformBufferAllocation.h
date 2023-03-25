#pragma once
#include "Rendering/Memory/Allocators/VMAAllocator.h"
#include "Rendering/Memory/BufferAllocations/UniformBufferAllocations/BaseUniformBufferAllocation.h"

class VMAUniformBufferAllocation : public BaseUniformBufferAllocation {
public:
	VMAUniformBufferAllocation(const VMAAllocator& allocator, const uint32_t dataSize);
	VMAUniformBufferAllocation(VMAUniformBufferAllocation&) = delete;
	~VMAUniformBufferAllocation();
	VMAUniformBufferAllocation& operator=(VMAUniformBufferAllocation&) = delete;

	virtual void UpdateBuffer(const void* data) const override;

private:
	const VMAAllocator& allocator;
	VmaAllocation allocation;
	void* memLoc;
	VkDeviceSize bufferSize;
};