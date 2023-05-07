#pragma once
#include "Backends/Vulkan/Device.h"
#include "Backends/Vulkan/Descriptors/DescriptorLayouts/BaseDescriptorLayout.h"
#include "Utils/FileIOr.h"

class Pipeline {
public:
	Pipeline(const Device& device, const std::string vertexShader, const std::string fragmentShader, const std::vector<BaseDescriptorLayout*> descriptorLayouts, const std::vector<uint32_t> vertexSizes, const std::vector<VkFormat> vertexFormats);
	Pipeline(Pipeline&) = delete;
	~Pipeline();

	Pipeline& operator=(Pipeline&) = delete;

	const VkPipelineLayout& GetPipelineLayout() const;
	const VkPipeline& GetGraphicsPipeline() const;
	void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const;

private:
	const Device& device;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkShaderModule createShaderModule(const std::string shaderPath);
};