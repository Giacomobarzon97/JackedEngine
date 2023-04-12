#include "CubeGeometry.h"

const std::string CubeGeometry::id = "CubeGeometry";

const std::vector<uint32_t> CubeGeometry::indexData = {
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
};

const std::vector<CPUPositionVertex> CubeGeometry::positionData = {
	CPUPositionVertex({-1,-1,-1,1}),
	CPUPositionVertex({1,-1,-1,1}),
	CPUPositionVertex({-1,1,-1,1}),
	CPUPositionVertex({-1,1,-1,1}),
	CPUPositionVertex({1,-1,-1,1}),
	CPUPositionVertex({1,1,-1,1}),
	CPUPositionVertex({1,-1,-1,1}),
	CPUPositionVertex({1,-1,1,1}),
	CPUPositionVertex({1,1,-1,1}),
	CPUPositionVertex({1,1,-1,1}),
	CPUPositionVertex({1,-1,1,1}),
	CPUPositionVertex({1,1,1,1}),
	CPUPositionVertex({1,-1,1,1}),
	CPUPositionVertex({-1,-1,1,1}),
	CPUPositionVertex({1,1,1,1}),
	CPUPositionVertex({1,1,1,1}),
	CPUPositionVertex({-1,-1,1,1}),
	CPUPositionVertex({-1,1,1,1}),
	CPUPositionVertex({-1,-1,1,1}),
	CPUPositionVertex({-1,-1,-1,1}),
	CPUPositionVertex({-1,1,1,1}),
	CPUPositionVertex({-1,1,1,1}),
	CPUPositionVertex({-1,-1,-1,1}),
	CPUPositionVertex({-1,1,-1,1}),
	CPUPositionVertex({-1,1,-1,1}),
	CPUPositionVertex({1,1,-1,1}),
	CPUPositionVertex({-1,1,1,1}),
	CPUPositionVertex({-1,1,1,1}),
	CPUPositionVertex({1,1,-1,1}),
	CPUPositionVertex({1,1,1,1}),
	CPUPositionVertex({-1,-1,1,1}),
	CPUPositionVertex({1,-1,1,1}),
	CPUPositionVertex({-1,-1,-1,1}),
	CPUPositionVertex({-1,-1,-1,1}),
	CPUPositionVertex({1,-1,1,1}),
	CPUPositionVertex({1,-1,-1,1})
};

const std::vector<CPUTextureVertex> CubeGeometry::texCoordData = {
	CPUTextureVertex({0,0}),
	CPUTextureVertex({0,0}),
	CPUTextureVertex({0,1}),
	CPUTextureVertex({0,1}),
	CPUTextureVertex({0,0}),
	CPUTextureVertex({1,0}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({0,0}),
	CPUTextureVertex({0,0}),
	CPUTextureVertex({0,1}),
	CPUTextureVertex({0,1}),
	CPUTextureVertex({0,0}),
	CPUTextureVertex({1,0}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({0,0}),
	CPUTextureVertex({0,0}),
	CPUTextureVertex({0,1}),
	CPUTextureVertex({0,1}),
	CPUTextureVertex({0,0}),
	CPUTextureVertex({1,0}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({-1,0}),
	CPUTextureVertex({1,0}),
	CPUTextureVertex({-1,1}),
	CPUTextureVertex({-1,1}),
	CPUTextureVertex({1,0}),
	CPUTextureVertex({1,0}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({1,0}),
	CPUTextureVertex({1,0}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({1,1})
};

const std::vector<uint32_t>& CubeGeometry::GetIndexData() const {
	return indexData;
}

const std::vector<CPUPositionVertex>& CubeGeometry::GetPositionData() const {
	return positionData;
}

const std::vector<CPUTextureVertex>& CubeGeometry::GetTexCoordData() const {
	return texCoordData;
}

const std::string& CubeGeometry::GetId() const {
	return id;
}
