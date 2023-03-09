#pragma once
#include <vulkan/vulkan.h>

class BaseBufferAllocation {
public:
	virtual ~BaseBufferAllocation();
	const VkBuffer GetBuffer() const;

protected:
	VkBuffer buffer;
};