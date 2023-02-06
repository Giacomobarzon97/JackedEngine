#pragma once

#include "Rendering/Device.h"
#include "Rendering/Pipeline.h"
#include "Rendering/Buffers/VertexBuffer.h"

class CommandBuffer {
public:
	CommandBuffer(const Device* const device);
	CommandBuffer(CommandBuffer&) = delete;
	~CommandBuffer();

	CommandBuffer &operator=(CommandBuffer &) = delete;

	const VkResult PresentCommand(const Pipeline* const pipeline, const VertexBuffer* const vertexBuffer) const;

private:
	const Device* const device;
	VkCommandBuffer commandBuffer;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
};