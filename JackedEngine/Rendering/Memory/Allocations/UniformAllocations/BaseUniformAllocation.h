#pragma once
#include <vulkan/vulkan.h>

class BaseUniformAllocation {
public:
	virtual ~BaseUniformAllocation() = 0;
	virtual void UpdateBuffer(const void* data) const = 0;
	const VkBuffer& GetBuffer() const;

protected:
	VkBuffer buffer;
};