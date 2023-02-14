#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "Utils/FileIOr.h"
#include "Logic/Vertex.h"
#include "Rendering/Device.h"
#include "Rendering/Descriptors/DescriptorPools/BaseDescriptorPool.h"

class Pipeline {
public:
	Pipeline(const Device& device, const BaseDescriptorPool& descriptorPool, const std::string shaderName = "default");
	Pipeline(Pipeline &) = delete;
	~Pipeline();
	Pipeline &operator=(Pipeline &) = delete;

	const VkPipelineLayout& GetPipelineLayout() const;
	const VkPipeline& GetGraphicsPipeline() const;
	void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const;

private:
	const Device& device;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkShaderModule createShaderModule(const std::vector<char>& code);
};