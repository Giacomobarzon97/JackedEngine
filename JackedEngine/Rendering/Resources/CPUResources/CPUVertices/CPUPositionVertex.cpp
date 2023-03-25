#include "CPUPositionVertex.h"

CPUPositionVertex::CPUPositionVertex(glm::vec4 position):
	position(position)
{}

VkFormat CPUPositionVertex::GetPositionCoordFormat() {
	return VK_FORMAT_R32G32B32A32_SFLOAT;
}

