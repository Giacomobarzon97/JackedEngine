#pragma once
#include <vulkan/vulkan.h>

class BaseAllocation {
public:
	virtual ~BaseAllocation();
	const VkBuffer GetBuffer() const;
	virtual const uint32_t GetOffset() const = 0;

protected:
	VkBuffer buffer;

private:

};