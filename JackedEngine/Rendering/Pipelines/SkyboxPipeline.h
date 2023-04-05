#pragma once
#include "Rendering/Pipelines/BasePipeline.h"
#include "Rendering/Descriptors/DescriptorLayouts/FrameDescriptorLayout.h"
#include "Rendering/Descriptors/DescriptorLayouts/SkyboxDescriptorLayout.h"
#include "Rendering/Resources/CPUResources/CPUVertices/CPUPositionVertex.h"

class SkyboxPipeline : public BasePipeline {
public:
	SkyboxPipeline(const Device& device, const FrameDescriptorLayout& uboDescriptorLayout, const SkyboxDescriptorLayout& objectDescriptorLayout);
	SkyboxPipeline(SkyboxPipeline&) = delete;

	SkyboxPipeline& operator=(SkyboxPipeline&) = delete;

	virtual void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const override;
};