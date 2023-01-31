#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

class Vertex {
public:
	Vertex(glm::vec2 position, glm::vec3 color);

	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();

private:
	glm::vec2 position;
	glm::vec3 color;
};