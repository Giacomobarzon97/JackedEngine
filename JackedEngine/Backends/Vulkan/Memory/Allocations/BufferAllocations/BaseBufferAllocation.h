#pragma once
#include <vulkan/vulkan.h>

class BaseBufferAllocation {
public:
	virtual ~BaseBufferAllocation() = 0;
	const VkBuffer& GetBuffer() const;

protected:
	VkBuffer buffer;
};