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

std::vector<VkPushConstantRange> BasePipeline::getPushConstants() {
	std::vector<VkPushConstantRange> push_constants(1);
	push_constants[0].offset = 0;
	push_constants[0].size = sizeof(PushConstants);
	push_constants[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	return push_constants;
}

void BasePipeline::GetPushConstantsConfig(std::vector<uint32_t>& offsets, std::vector<uint32_t>& sizes, std::vector<VkShaderStageFlags>& stageFlags) {
	offsets.resize(1);
	sizes.resize(1);
	stageFlags.resize(1);

	offsets[0] = 0;
	sizes[0] = sizeof(PushConstants);
	stageFlags[0] = VK_SHADER_STAGE_VERTEX_BIT;
}
