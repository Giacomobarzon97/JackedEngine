#include "BaseCommandBuffer.h"

BaseCommandBuffer::BaseCommandBuffer(const Device& device) :
	device(device)
{
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = device.GetCommandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;
	if (vkAllocateCommandBuffers(device.GetLogicalDevice(), &allocInfo, &commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
}

BaseCommandBuffer::~BaseCommandBuffer(){}