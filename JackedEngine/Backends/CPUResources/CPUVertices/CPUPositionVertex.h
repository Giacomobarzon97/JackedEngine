#pragma once

#include <glm/glm.hpp>
#include <array>

class CPUPositionVertex {
public:
	CPUPositionVertex(const glm::vec4 position);
private:
	glm::vec4 position;
};