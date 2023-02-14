#pragma once

#include "Rendering/Device.h"
#include "Rendering/Pipeline.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"

class CommandBuffer {
public:
	CommandBuffer(const Device& device);
	CommandBuffer(CommandBuffer&) = delete;
	~CommandBuffer();

	CommandBuffer &operator=(CommandBuffer &) = delete;

	const VkResult PresentCommand(const Pipeline& pipeline, const VertexBuffer& vertexBuffer, const BaseDescriptorSet& descriptorSet) const;

private:
	const Device& device;
	VkCommandBuffer commandBuffer;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
};