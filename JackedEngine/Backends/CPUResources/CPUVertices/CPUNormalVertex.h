#pragma once

#include <glm/glm.hpp>
#include "Backends/BackendTypes.h"

class CPUNormalVertex {
public:
	CPUNormalVertex(const glm::vec3 normal);

	static uint8_t GetNumberOfComponents();
	static VertexType GetVertexType();

private:
	glm::vec3 normal;
};