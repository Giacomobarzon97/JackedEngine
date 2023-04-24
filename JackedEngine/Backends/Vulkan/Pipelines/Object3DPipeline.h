#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "Utils/FileIOr.h"
#include "Backends/CPUResources/CPUVertices/CPUPositionVertex.h"
#include "Backends/CPUResources/CPUVertices/CPUTextureVertex.h"
#include "Backends/Vulkan/Device.h"
#include "Backends/Vulkan/Pipelines/BasePipeline.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/FrameDescriptorLayout.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/MaterialDescriptorLayout.h"

class Object3DPipeline : public BasePipeline{
public:
	Object3DPipeline(const Device& device, const FrameDescriptorLayout& uboDescriptorLayout, const MaterialDescriptorLayout& objectDescriptorLayout);
	Object3DPipeline(Object3DPipeline&) = delete;

	Object3DPipeline&operator=(Object3DPipeline&) = delete;

	virtual void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const override;
};