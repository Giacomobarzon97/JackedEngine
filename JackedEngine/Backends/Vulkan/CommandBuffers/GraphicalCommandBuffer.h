#pragma once

#include "Backends/Vulkan/Device.h"
#include "Backends/Vulkan/GPUResources/GPUModel.h"
#include "Backends/Vulkan/Pipelines/BasePipeline.h"
#include "Backends/Vulkan/Descriptors/DescriptorSets/UniformDescriptorSet.h"
#include "Backends/Vulkan/Descriptors/DescriptorSets/ImageDescriptorSet.h"
#include "Backends/Vulkan/CommandBuffers/BaseCommandBuffer.h"

class GraphicalCommandBuffer : public BaseCommandBuffer{
public:
	GraphicalCommandBuffer(Device& device);
	GraphicalCommandBuffer(GraphicalCommandBuffer&) = delete;
	~GraphicalCommandBuffer();

	GraphicalCommandBuffer&operator=(GraphicalCommandBuffer&) = delete;

	void BeginRenderPass();
	void BindPipeline(const BasePipeline& pipeline);
	void BindModel(const GPUModel& model);
	void BindDescriptorSet(const BaseDescriptorSet& descriptorSet, const uint32_t location);
	void Draw() const;
	const VkResult EndRenderPass();

private:
	enum class CommandBufferState {Idle, Recording};

	Device& device;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
	uint32_t imageIndex;
	CommandBufferState currentState = CommandBufferState::Idle;
	std::optional<const BasePipeline*> bindedPipeline;
	std::optional<const GPUModel*> bindedModel;
};