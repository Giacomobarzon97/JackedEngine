#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

class CPUVertex {
public:
	CPUVertex(const glm::vec4 position, const glm::vec2 textCoord);

	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();

private:
	glm::vec4 position;
	glm::vec2 texCoord;

};