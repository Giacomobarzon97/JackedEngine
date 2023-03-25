#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

class CPUTextureVertex {
public:
	CPUTextureVertex(const glm::vec2 textCoord);

	static VkFormat GetTexCoordFormat();

private:
	glm::vec2 texCoord;

};