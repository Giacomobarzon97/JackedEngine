#pragma once

#include "Rendering/Device.h"
#include "Rendering/Pipeline.h"
#include "Rendering/VertexBuffer.h"

class CommandBuffer {
public:
	CommandBuffer(Device* device);
	CommandBuffer(CommandBuffer&) = delete;
	~CommandBuffer();

	CommandBuffer &operator=(CommandBuffer &) = delete;

	VkResult PresentCommand(Pipeline* pipeline, VertexBuffer* vertexBuffer);

private:
	Device* device;
	VkCommandBuffer commandBuffer;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
};