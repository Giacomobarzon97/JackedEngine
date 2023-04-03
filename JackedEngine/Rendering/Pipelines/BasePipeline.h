#pragma once
#include <glm/glm.hpp>
#include "Utils/FileIOr.h"
#include "Rendering/Device.h"

class BasePipeline {
public:
	BasePipeline(const Device& device);
	virtual ~BasePipeline();

	const VkPipelineLayout& GetPipelineLayout() const;
	const VkPipeline& GetGraphicsPipeline() const;
	virtual void GetScreenData(VkViewport& viewport, VkRect2D& scissor) const = 0;
	virtual void GetPushConstantsData(std::vector<uint32_t>& offsets, std::vector<uint32_t>& sizes, std::vector<VkShaderStageFlags>& stageFlags) const = 0;

protected:
	struct PushConstants {
		glm::mat4 modelMatrix;
	};

	const Device& device;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkShaderModule createShaderModule(const std::string shaderPath);
};