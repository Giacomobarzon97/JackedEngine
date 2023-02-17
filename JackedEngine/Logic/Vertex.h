#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

class Vertex {
public:
	Vertex(const glm::vec4 position, const glm::vec4 color);

	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();

private:
	glm::vec4 position;
	glm::vec4 color;
};