#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "Utils/FileIOr.h"
#include "Rendering/Device.h"
#include "Logic/Vertex.h"

class Pipeline {
public:
	Pipeline(const Device* const device, const std::string shaderName = "default");
	Pipeline(Pipeline &) = delete;
	~Pipeline();
	Pipeline &operator=(Pipeline &) = delete;

	const VkPipeline* const GetGraphicsPipeline() const;
	void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const;

private:
	const Device * const device;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkShaderModule createShaderModule(const std::vector<char>& code);
};