#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

class CPUPositionVertex {
public:
	CPUPositionVertex(const glm::vec4 position);

	static VkFormat GetPositionCoordFormat();

private:
	glm::vec4 position;
};