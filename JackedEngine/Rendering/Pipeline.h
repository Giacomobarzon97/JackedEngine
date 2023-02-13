#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "Utils/FileIOr.h"
#include "Rendering/Device.h"
#include "Logic/Vertex.h"

class Pipeline {
public:
	Pipeline(const Device* const device, int nFrames, const std::string shaderName = "default");
	Pipeline(Pipeline &) = delete;
	~Pipeline();
	Pipeline &operator=(Pipeline &) = delete;

	const VkPipelineLayout* const GetPipelineLayout() const;
	const VkPipeline* const GetGraphicsPipeline() const;
	void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const;
	const VkDescriptorSetLayout* const GetDescriptorSetLayout() const;
	const VkDescriptorPool* const GetDescriptorPool() const;

private:
	const Device * const device;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorPool descriptorPool;

	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createDescriptors();
};