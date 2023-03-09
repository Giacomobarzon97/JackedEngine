#pragma once

#include "Rendering/Resources/CPUResources/CPUModel.h"
#include "Rendering/Device.h"
#include "Rendering/Pipelines/BasePipeline.h"
#include "Rendering/Resources/GPUResources/GPUModel.h"
#include "Rendering/Descriptors/DescriptorSets/UBODescriptorSet.h"
#include "Rendering/Descriptors/DescriptorSets/ImageDescriptorSet.h"
#include "Rendering/CommandBuffers/BaseCommandBuffer.h"

class Graphical3DCommandBuffer : public BaseCommandBuffer{
public:
	Graphical3DCommandBuffer(const Device& device);
	Graphical3DCommandBuffer(Graphical3DCommandBuffer&) = delete;
	~Graphical3DCommandBuffer();

	Graphical3DCommandBuffer&operator=(Graphical3DCommandBuffer&) = delete;

	const VkResult PresentCommand(const BasePipeline& pipeline, const GPUModel& model, const UBODescriptorSet& uboDescriptorSet, const ImageDescriptorSet& imageDescriptorSet) const;

private:
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
};