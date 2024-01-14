#include "CPUQuadModel.h"

const std::string CPUQuadModel::id = "QuadModel";

const std::array<uint32_t, 6> CPUQuadModel::indexData = {
	0,1,2,
	0,3,1
};

const std::array<CPUPositionVertex, 4> CPUQuadModel::positionData = {
	CPUPositionVertex({-1,0,-1}),
	CPUPositionVertex({1,0,1}),
	CPUPositionVertex({1,0,-1}),
	CPUPositionVertex({-1,0,1})
};

const std::array<CPUTextureVertex, 4> CPUQuadModel::texCoordData = {
	CPUTextureVertex({0,0}),
	CPUTextureVertex({1,1}),
	CPUTextureVertex({1,0}),
	CPUTextureVertex({0,1})
};

const std::array<CPUNormalVertex, 4> CPUQuadModel::normalData = {
	CPUNormalVertex({1, 1, 0}),
	CPUNormalVertex({1, 1, 0}),
	CPUNormalVertex({1, 1, 0}),
	CPUNormalVertex({1, 1, 0})
};

void CPUQuadModel::LoadData() {
	data.vertexData.push_back(
		BufferData{
			positionData.data(),
			static_cast<uint32_t>(sizeof(CPUPositionVertex) * positionData.size())
		}
	);
	data.vertexData.push_back(
		BufferData{
			texCoordData.data(),
			static_cast<uint32_t>(sizeof(CPUTextureVertex) * positionData.size())
		}
	);
	data.vertexData.push_back(
		BufferData{
			normalData.data(),
			static_cast<uint32_t>(sizeof(CPUNormalVertex) * positionData.size())
		}
	);

	data.indexData.data = indexData.data();
	data.indexData.size = sizeof(uint32_t) * static_cast<uint32_t>(indexData.size());
	data.numberOfIndices = 6;
}

/*
	TODO:: Should throw error when is called before LoadData
*/
const ModelData CPUQuadModel::GetModelData() const {
	return data;
}


const std::string& CPUQuadModel::GetId() const {
	return id;
}
