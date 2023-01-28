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
	Pipeline(Pipeline &) = delete;
	~Pipeline();
	Pipeline &operator=(Pipeline &) = delete;

	VkPipeline* GetGraphicsPipeline();

private:
	Device * device;
	SwapChain* swapChain;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkShaderModule createShaderModule(const std::vector<char>& code);
};