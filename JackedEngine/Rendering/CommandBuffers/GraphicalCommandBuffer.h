#pragma once

#include "Rendering/Device.h"
#include "Rendering/Resources/GPUResources/GPUModel.h"
#include "Rendering/Pipelines/BasePipeline.h"
#include "Rendering/Descriptors/DescriptorSets/FrameDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorSets/ObjectDescriptorSet.h"
#include "Rendering/CommandBuffers/BaseCommandBuffer.h"

#include "Rendering/Descriptors/DescriptorSets/SkyboxDescriptorSet.h"
#include "Rendering/Pipelines/SkyboxPipeline.h"

class GraphicalCommandBuffer : public BaseCommandBuffer{
public:
	GraphicalCommandBuffer(Device& device);
	GraphicalCommandBuffer(GraphicalCommandBuffer&) = delete;
	~GraphicalCommandBuffer();

	GraphicalCommandBuffer&operator=(GraphicalCommandBuffer&) = delete;

	void BeginRenderPass();
	const VkResult EndRenderPass();
	void NextSubpass();
	void Draw(const BasePipeline& pipeline, const GPUModel& model, const void* constantsData, const FrameDescriptorSet& frameDescriptorSet, const BaseDescriptorSet& objectDescriptorSet) const;

private:
	enum class CommandBufferState {Idle, Recording};

	Device& device;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
	uint32_t imageIndex;
	CommandBufferState currentState = CommandBufferState::Idle;
};