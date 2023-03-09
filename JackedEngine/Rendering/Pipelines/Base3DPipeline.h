#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "Utils/FileIOr.h"
#include "Rendering/Resources/CPUResources/CPUVertex.h"
#include "Rendering/Device.h"
#include "Rendering/Pipelines/BasePipeline.h"
#include "Rendering/Descriptors/DescriptorPools/UBODescriptorPool.h"
#include "Rendering/Descriptors/DescriptorPools/ImageDescriptorPool.h"

class Base3DPipeline : public BasePipeline{
public:
	Base3DPipeline(const Device& device, const UBODescriptorPool& uboDescriptorPool, const ImageDescriptorPool& imageDescriptorPool, const std::string shaderName = "default");
	Base3DPipeline(Base3DPipeline&) = delete;

	Base3DPipeline&operator=(Base3DPipeline&) = delete;

	virtual void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const override;
};