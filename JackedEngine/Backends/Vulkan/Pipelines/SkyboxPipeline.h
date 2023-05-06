#pragma once
#include "Backends/Vulkan/Pipelines/BasePipeline.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/UniformDescriptorLayout.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/ImageDescriptorLayout.h"
#include "Backends/CPUResources/CPUVertices/CPUPositionVertex.h"

class SkyboxPipeline : public BasePipeline {
public:
	SkyboxPipeline(const Device& device, const UniformDescriptorLayout& uniformDescriptorLayout, const ImageDescriptorLayout& imageDescriptorLayout);
	SkyboxPipeline(SkyboxPipeline&) = delete;

	SkyboxPipeline& operator=(SkyboxPipeline&) = delete;

	virtual void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const override;
};