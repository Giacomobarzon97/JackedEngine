#include "CPUCubeModel.h"

const std::string CPUCubeModel::id = "CubeModel";

const std::vector<uint32_t> CPUCubeModel::indexData = {
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

const std::vector<CPUPositionVertex> CPUCubeModel::positionData = {
	CPUPositionVertex({-1,-1,-1}),
	CPUPositionVertex({1,-1,-1}),
	CPUPositionVertex({-1,1,-1}),
	CPUPositionVertex({-1,1,-1}),
	CPUPositionVertex({1,-1,-1}),
	CPUPositionVertex({1,1,-1}),
	CPUPositionVertex({1,-1,-1}),
	CPUPositionVertex({1,-1,1}),
	CPUPositionVertex({1,1,-1}),
	CPUPositionVertex({1,1,-1}),
	CPUPositionVertex({1,-1,1}),
	CPUPositionVertex({1,1,1}),
	CPUPositionVertex({1,-1,1}),
	CPUPositionVertex({-1,-1,1}),
	CPUPositionVertex({1,1,1}),
	CPUPositionVertex({1,1,1}),
	CPUPositionVertex({-1,-1,1}),
	CPUPositionVertex({-1,1,1}),
	CPUPositionVertex({-1,-1,1}),
	CPUPositionVertex({-1,-1,-1}),
	CPUPositionVertex({-1,1,1}),
	CPUPositionVertex({-1,1,1}),
	CPUPositionVertex({-1,-1,-1}),
	CPUPositionVertex({-1,1,-1}),
	CPUPositionVertex({-1,1,-1}),
	CPUPositionVertex({1,1,-1}),
	CPUPositionVertex({-1,1,1}),
	CPUPositionVertex({-1,1,1}),
	CPUPositionVertex({1,1,-1}),
	CPUPositionVertex({1,1,1}),
	CPUPositionVertex({-1,-1,1}),
	CPUPositionVertex({1,-1,1}),
	CPUPositionVertex({-1,-1,-1}),
	CPUPositionVertex({-1,-1,-1}),
	CPUPositionVertex({1,-1,1}),
	CPUPositionVertex({1,-1,-1})
};

const std::vector<CPUTextureVertex> CPUCubeModel::texCoordData = {
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

CPUCubeModel::CPUCubeModel(const bool includePositions, const bool includeTexcoords) :
	includePositions(includePositions),
	includeTexcoords(includeTexcoords)
{}

void CPUCubeModel::LoadData() {}

/*
	TODO:: Should throw error when is called before LoadData
*/
const ModelData CPUCubeModel::GetModelData() const {
	ModelData data{};

	if (includePositions) {
		data.vertexData.push_back(
			BufferData{
				positionData.data(),
				static_cast<uint32_t>(sizeof(CPUPositionVertex) * positionData.size())
			}
		);
	}

	if (includeTexcoords) {
		data.vertexData.push_back(
			BufferData{
				texCoordData.data(),
				static_cast<uint32_t>(sizeof(CPUTextureVertex) * positionData.size())
			}
		);
	}

	data.indexData.data = indexData.data();
	data.indexData.size = sizeof(uint32_t) * static_cast<uint32_t>(indexData.size());
	data.numberOfIndices = 36;

	return data;
}


const std::string& CPUCubeModel::GetId() const {
	return id;
}
