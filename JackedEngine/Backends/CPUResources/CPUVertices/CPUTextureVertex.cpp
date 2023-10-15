#include "CPUTextureVertex.h"

CPUTextureVertex::CPUTextureVertex(glm::vec2 texCoord) :
	texCoord(texCoord)
{}

uint8_t CPUTextureVertex::GetNumberOfComponents() {
	return 2;
}

VertexType CPUTextureVertex::GetVertexType() {
	return FLOAT_32;
}