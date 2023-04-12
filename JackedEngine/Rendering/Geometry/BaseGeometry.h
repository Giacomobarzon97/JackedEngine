#pragma once
#include <vector>
#include <string>
#include "Rendering/Resources/CPUResources/CPUVertices/CPUPositionVertex.h"
#include "Rendering/Resources/CPUResources/CPUVertices/CPUTextureVertex.h"

class BaseGeometry {
	public:
		virtual ~BaseGeometry();

		virtual const std::vector<uint32_t>& GetIndexData() const = 0;
		virtual const std::vector<CPUPositionVertex>& GetPositionData() const = 0;
		virtual const std::vector<CPUTextureVertex>& GetTexCoordData() const = 0;
		virtual const std::string& GetId() const = 0;
};