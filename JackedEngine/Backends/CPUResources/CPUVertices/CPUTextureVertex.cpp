#include "CPUTextureVertex.h"

CPUTextureVertex::CPUTextureVertex(glm::vec2 texCoord) :
	texCoord(texCoord)
{}

VkFormat CPUTextureVertex::GetTexCoordFormat() {
	return VK_FORMAT_R32G32_SFLOAT;
}