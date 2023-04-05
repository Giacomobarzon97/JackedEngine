#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "Utils/FileIOr.h"
#include "Rendering/Resources/CPUResources/CPUVertices/CPUPositionVertex.h"
#include "Rendering/Resources/CPUResources/CPUVertices/CPUTextureVertex.h"
#include "Rendering/Device.h"
#include "Rendering/Pipelines/BasePipeline.h"
#include "Rendering/Descriptors/DescriptorLayouts/FrameDescriptorLayout.h"
#include "Rendering/Descriptors/DescriptorLayouts/ObjectDescriptorLayout.h"

class Object3DPipeline : public BasePipeline{
public:
	Object3DPipeline(const Device& device, const FrameDescriptorLayout& uboDescriptorLayout, const ObjectDescriptorLayout& objectDescriptorLayout);
	Object3DPipeline(Object3DPipeline&) = delete;

	Object3DPipeline&operator=(Object3DPipeline&) = delete;

	virtual void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const override;
};