#include "CPUCubeModel.h"

const std::string CPUCubeModel::id = "CubeModel";

const std::array<uint32_t, 36> CPUCubeModel::indexData = {
	0,1,2,3,4,5, //left
	6,7,8,9,10,11,//front
	12,13,14,15,16,17,//right
	18,19,20,21,22,23,//back
	24,25,26,27,28,29, //top
	30,31,32,33,34,35, //bottom
};

const std::array<CPUPositionVertex, 36> CPUCubeModel::positionData = {
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

const std::array<CPUTextureVertex, 36> CPUCubeModel::texCoordData = {
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

const std::array<CPUNormalVertex, 36> CPUCubeModel::normalData = {
	CPUNormalVertex({0, 0, 1}),
	CPUNormalVertex({0, 0, 1}),
	CPUNormalVertex({0, 0, 1}),
	CPUNormalVertex({0, 0, 1}),
	CPUNormalVertex({0, 0, 1}),
	CPUNormalVertex({0, 0, 1}),

	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	CPUNormalVertex({1, 0, 0}),
	
	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	CPUNormalVertex({0, 1, 1}),
	
	CPUNormalVertex({1, 1, 0}),
	CPUNormalVertex({1, 1, 0}),
	CPUNormalVertex({1, 1, 0}),
	CPUNormalVertex({1, 1, 0}),
	CPUNormalVertex({1, 1, 0}),
	CPUNormalVertex({1, 1, 0})
};

void CPUCubeModel::LoadData() {
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
	data.numberOfIndices = 36;
}

/*
	TODO:: Should throw error when is called before LoadData
*/
const ModelData CPUCubeModel::GetModelData() const {
	return data;
}


const std::string& CPUCubeModel::GetId() const {
	return id;
}
