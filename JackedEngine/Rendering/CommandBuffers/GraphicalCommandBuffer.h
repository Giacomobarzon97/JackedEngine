#pragma once

#include "Rendering/Resources/CPUResources/CPUModel.h"
#include "Rendering/Device.h"
#include "Rendering/Pipelines/Object3DPipeline.h"
#include "Rendering/Resources/GPUResources/GPUTexturedModel.h"
#include "Rendering/Descriptors/DescriptorSets/FrameDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorSets/ObjectDescriptorSet.h"
#include "Rendering/CommandBuffers/BaseCommandBuffer.h"

class GraphicalCommandBuffer : public BaseCommandBuffer{
public:
	GraphicalCommandBuffer(const Device& device);
	GraphicalCommandBuffer(GraphicalCommandBuffer&) = delete;
	~GraphicalCommandBuffer();

	GraphicalCommandBuffer&operator=(GraphicalCommandBuffer&) = delete;

	const VkResult DrawObject(const Object3DPipeline& pipeline, const GPUTexturedModel& model, const FrameDescriptorSet& frameDescriptorSet, const ObjectDescriptorSet& objectDescriptorSet) const;

private:
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
};