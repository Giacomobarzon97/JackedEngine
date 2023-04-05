#pragma once
#include <vulkan/vulkan.h>

class BaseIndexBufferAllocation{
public:
	virtual ~BaseIndexBufferAllocation() = 0;
	const VkBuffer& GetBuffer() const;

protected:
	VkBuffer buffer;
};