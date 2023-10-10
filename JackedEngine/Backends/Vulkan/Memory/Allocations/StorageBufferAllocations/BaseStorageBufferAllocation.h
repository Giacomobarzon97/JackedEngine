#pragma once
#include <vulkan/vulkan.h>

class BaseStorageBufferAllocation {
public:
	BaseStorageBufferAllocation(const uint32_t elementSize, const uint32_t nElements);
	virtual ~BaseStorageBufferAllocation() = 0;

	virtual void UpdateBuffer(const void* data, const uint32_t nElements) const = 0;
	const VkBuffer& GetBuffer() const;

protected:
	VkBuffer buffer;
	const uint32_t elementSize;
	const uint32_t nElements;
};