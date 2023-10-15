#pragma once

#include <glm/glm.hpp>
#include "Backends/BackendTypes.h"

class CPUTextureVertex {
public:
	CPUTextureVertex(const glm::vec2 textCoord);

	static uint8_t GetNumberOfComponents();
	static VertexType GetVertexType();

private:
	glm::vec2 texCoord;

};