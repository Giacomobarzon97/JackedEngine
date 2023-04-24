#pragma once

#include "Backends/Vulkan/Device.h"
#include "Backends/Vulkan/GPUResources/GPUModel.h"
#include "Backends/Vulkan/Pipelines/BasePipeline.h"
#include "Backends/Vulkan/Descriptors/DescriptorSets/FrameDescriptorSet.h"
#include "Backends/Vulkan/Descriptors/DescriptorSets/MaterialDescriptorSet.h"
#include "Backends/Vulkan/CommandBuffers/BaseCommandBuffer.h"

class GraphicalCommandBuffer : public BaseCommandBuffer{
public:
	GraphicalCommandBuffer(Device& device);
	GraphicalCommandBuffer(GraphicalCommandBuffer&) = delete;
	~GraphicalCommandBuffer();

	GraphicalCommandBuffer&operator=(GraphicalCommandBuffer&) = delete;

	void BeginRenderPass();
	const VkResult EndRenderPass();
	void NextSubpass();
	void Draw(const BasePipeline& pipeline, const GPUModel& model, const void* constantsData, const FrameDescriptorSet& frameDescriptorSet, const MaterialDescriptorSet& materialDescriptorSet) const;

private:
	enum class CommandBufferState {Idle, Recording};

	Device& device;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
	uint32_t imageIndex;
	CommandBufferState currentState = CommandBufferState::Idle;
};