#include "GPUBaseModel.h"

GPUBaseModel::GPUBaseModel(const BaseAllocationFactory& allocationFactory, const CPUModel& model) {
	positionsBufferAllocation = allocationFactory.CreateVertexBufferAllocation(
		model.GetPositionVertexData(),
		sizeof(CPUPositionVertex) * model.GetNumberOfVertices()
	);
	
	indexBufferAllocation = allocationFactory.CreateIndexBufferAllocation(
		model.GetIndexData(),
		CPUModel::GetIndexSize() * model.GetNumberOfIndices()
	);

	nVertices = static_cast<uint32_t>(model.GetNumberOfIndices());
}

GPUBaseModel::~GPUBaseModel() {
	delete positionsBufferAllocation;
	delete indexBufferAllocation;
}

const BaseVertexBufferAllocation& GPUBaseModel::GetPositionsBufferAllocation() const {
	return *positionsBufferAllocation;
}

const BaseIndexBufferAllocation& GPUBaseModel::GetIndexBufferAllocation() const {
	return *indexBufferAllocation;
}

const uint32_t GPUBaseModel::GetNumberOfIndices() const {
	return nVertices;
}