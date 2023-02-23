#pragma once
#include "Utils/FileIOr.h"
#include "Rendering/Device.h"

class BasePipeline {
public:
	BasePipeline(const Device& device);
	BasePipeline(BasePipeline&) = delete;
	virtual ~BasePipeline();
	BasePipeline& operator=(BasePipeline&) = delete;


	const VkPipelineLayout& GetPipelineLayout() const;
	const VkPipeline& GetGraphicsPipeline() const;
	virtual void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const = 0;

protected:
	const Device& device;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkShaderModule createShaderModule(const std::string shaderPath);
};