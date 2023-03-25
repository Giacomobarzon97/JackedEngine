#pragma once

#include "Rendering/Resources/CPUResources/CPUModel.h"
#include "Rendering/Device.h"
#include "Rendering/Pipelines/Object3DPipeline.h"
#include "Rendering/Resources/GPUResources/GPUModel.h"
#include "Rendering/Descriptors/DescriptorSets/FrameDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorSets/ObjectDescriptorSet.h"
#include "Rendering/CommandBuffers/BaseCommandBuffer.h"

class GraphicalCommandBuffer : public BaseCommandBuffer{
public:
	GraphicalCommandBuffer(Device& device, const Object3DPipeline& object3DPipeline);
	GraphicalCommandBuffer(GraphicalCommandBuffer&) = delete;
	~GraphicalCommandBuffer();

	GraphicalCommandBuffer&operator=(GraphicalCommandBuffer&) = delete;

	void BeginRenderPass();
	const VkResult EndRenderPass();
	void Draw(const GPUModel& model, const FrameDescriptorSet& frameDescriptorSet, const ObjectDescriptorSet& objectDescriptorSet) const;

private:
	enum class CommandBufferState {Idle, Recording};

	const Object3DPipeline& object3DPipeline;
	Device& device;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
	uint32_t imageIndex;
	CommandBufferState currentState = CommandBufferState::Idle;
};