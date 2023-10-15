#pragma once

#include <glm/glm.hpp>
#include "Backends/BackendTypes.h"

class CPUPositionVertex {
public:
	CPUPositionVertex(const glm::vec3 position);

	static uint8_t GetNumberOfComponents();
	static VertexType GetVertexType();

private:
	glm::vec3 position;
};