#include "CPUNormalVertex.h"

CPUNormalVertex::CPUNormalVertex(glm::vec3 normal):
	normal(normal)
{}

uint8_t CPUNormalVertex::GetNumberOfComponents() {
	return 3;
}

VertexType CPUNormalVertex::GetVertexType() {
	return FLOAT_32;
}