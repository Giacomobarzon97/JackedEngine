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
	Pipeline(const Device* const device, const BaseDescriptorPool* const descriptorPool, const std::string shaderName = "default");
	Pipeline(Pipeline &) = delete;
	~Pipeline();
	Pipeline &operator=(Pipeline &) = delete;

	const VkPipelineLayout* const GetPipelineLayout() const;
	const VkPipeline* const GetGraphicsPipeline() const;
	void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const;

private:
	const Device * const device;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createDescriptors();
};