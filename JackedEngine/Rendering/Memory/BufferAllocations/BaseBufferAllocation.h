#pragma once
#include <vulkan/vulkan.h>

class BaseBufferAllocation {
public:
	virtual ~BaseBufferAllocation();
	const VkBuffer GetBuffer() const;
	virtual const VkDeviceSize GetOffset() const = 0;

protected:
	VkBuffer buffer;
};