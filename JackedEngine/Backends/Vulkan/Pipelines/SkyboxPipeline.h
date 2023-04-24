#pragma once
#include "Backends/Vulkan/Pipelines/BasePipeline.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/FrameDescriptorLayout.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/MaterialDescriptorLayout.h"
#include "Backends/CPUResources/CPUVertices/CPUPositionVertex.h"

class SkyboxPipeline : public BasePipeline {
public:
	SkyboxPipeline(const Device& device, const FrameDescriptorLayout& uboDescriptorLayout, const MaterialDescriptorLayout& objectDescriptorLayout);
	SkyboxPipeline(SkyboxPipeline&) = delete;

	SkyboxPipeline& operator=(SkyboxPipeline&) = delete;

	virtual void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const override;
};