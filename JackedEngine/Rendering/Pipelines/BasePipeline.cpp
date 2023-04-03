#include "BasePipeline.h"

BasePipeline::BasePipeline(const Device& device) :
	device(device)
{}

BasePipeline::~BasePipeline() {
	vkDestroyPipeline(device.GetLogicalDevice(), graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(device.GetLogicalDevice(), pipelineLayout, nullptr);
}

VkShaderModule BasePipeline::createShaderModule(const std::string shaderPath) {
	std::vector<char> shaderCode = FileIO::readFile(shaderPath);
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = shaderCode.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());
	VkShaderModule shaderModule;
	if (vkCreateShaderModule(device.GetLogicalDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}
	return shaderModule;
}

const VkPipelineLayout& BasePipeline::GetPipelineLayout() const {
	return pipelineLayout;
}

const VkPipeline& BasePipeline::GetGraphicsPipeline() const {
	return graphicsPipeline;
}