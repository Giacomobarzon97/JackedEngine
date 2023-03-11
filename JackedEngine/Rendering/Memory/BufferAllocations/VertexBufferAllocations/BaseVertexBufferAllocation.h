#pragma once
#include <vulkan/vulkan.h>

class BaseVertexBufferAllocation {
public:
	virtual ~BaseVertexBufferAllocation() = 0;
	const VkBuffer GetBuffer() const;

protected:
	VkBuffer buffer;
};