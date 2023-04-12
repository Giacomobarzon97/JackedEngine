#pragma once
#include "Rendering/Geometry/BaseGeometry.h"

class CubeGeometry : public BaseGeometry{
public:
	virtual const std::vector<uint32_t>& GetIndexData() const override;
	virtual const std::vector<CPUPositionVertex>& GetPositionData() const override;
	virtual const std::vector<CPUTextureVertex>& GetTexCoordData() const override;
	virtual const std::string& GetId() const override;

private:
	static const std::string id;
	static const std::vector<uint32_t> indexData;
	static const std::vector<CPUPositionVertex> positionData;
	static const std::vector<CPUTextureVertex> texCoordData;
};