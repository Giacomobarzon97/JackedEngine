#include "CPUPositionVertex.h"

CPUPositionVertex::CPUPositionVertex(glm::vec3 position):
	position(position)
{}

uint8_t CPUPositionVertex::GetNumberOfComponents() {
	return 3;
}

VertexType CPUPositionVertex::GetVertexType() {
	return FLOAT_32;
}
