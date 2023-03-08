#include "GPUModel.h"

GPUModel::GPUModel(const BaseAllocationFactory& allocationFactory, const std::string objFilePath) {
	Model model(objFilePath);
	
	vertexBufferAllocation = allocationFactory.CreateBufferAllocation(
		model.GetVertexData(),
		model.GetVertexSize() * model.GetNumberOfVertices()
	);
	
	indexBufferAllocation = allocationFactory.CreateBufferAllocation(
		model.GetIndexData(),
		model.GetIndexSize() * model.GetNumberOfIndices()
	);

	nVertices = static_cast<uint32_t>(model.GetNumberOfIndices());
}

GPUModel::~GPUModel() {
	delete vertexBufferAllocation;
	delete indexBufferAllocation;
}

const BaseBufferAllocation& GPUModel::GetVertexBufferAllocation() const {
	return *vertexBufferAllocation;
}

const BaseBufferAllocation& GPUModel::GetIndexBufferAllocation() const {
	return *indexBufferAllocation;
}

const uint32_t GPUModel::GetNumberOfIndices() const {
	return nVertices;
}