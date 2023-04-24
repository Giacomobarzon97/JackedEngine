#pragma once
#include "Backends/Vulkan/Device.h"

class BaseCommandBuffer {
public:
	BaseCommandBuffer(const Device& device);
	BaseCommandBuffer(BaseCommandBuffer&) = delete;
	virtual ~BaseCommandBuffer() = 0;

	BaseCommandBuffer& operator=(BaseCommandBuffer&) = delete;

protected:
	VkCommandBuffer commandBuffer;
};