#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "Utils/FileIOr.h"
#include "Rendering/Device.h"
#include "Rendering/SwapChain.h"

class Pipeline {
public:
	Pipeline(Device* device, SwapChain* swapChain, std::string vertShaderPath, std::string fragShaderPath);
	~Pipeline();

private:
	Device * device;
	SwapChain* swapChain;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkShaderModule createShaderModule(const std::vector<char>& code);

	VkPipelineVertexInputStateCreateInfo getVertexInputCreateInfo();
	VkPipelineInputAssemblyStateCreateInfo getInputAssemblyCreateInfo();
	VkPipelineViewportStateCreateInfo getViewportStateCreateInfo();
	VkPipelineRasterizationStateCreateInfo getRasterizationCreateInfo();
	VkPipelineMultisampleStateCreateInfo getMultisampleCreateInfo();
	VkPipelineColorBlendStateCreateInfo getColorBlendStateCreateInfo();
};