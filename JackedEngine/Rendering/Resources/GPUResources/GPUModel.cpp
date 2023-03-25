#include "GPUModel.h"

GPUModel::GPUModel(const BaseAllocationFactory& allocationFactory, const CPUModel& model)
{
	positionsBufferAllocation = allocationFactory.CreateVertexBufferAllocation(
		model.GetPositionVertexData(),
		sizeof(CPUPositionVertex) * model.GetNumberOfVertices()
	);
	
	texCoordsBufferAllocation = allocationFactory.CreateVertexBufferAllocation(
		model.GetTextureVertexData(),
		sizeof(CPUTextureVertex) * model.GetNumberOfVertices()
	);

	indexBufferAllocation = allocationFactory.CreateIndexBufferAllocation(
		model.GetIndexData(),
		CPUModel::GetIndexSize() * model.GetNumberOfIndices()
	);

	nVertices = static_cast<uint32_t>(model.GetNumberOfIndices());
}

GPUModel::~GPUModel() {
	delete positionsBufferAllocation;
	delete texCoordsBufferAllocation;
	delete indexBufferAllocation;
}

const BaseVertexBufferAllocation& GPUModel::GetPositionsBufferAllocation() const {
	return *positionsBufferAllocation;
}

const BaseVertexBufferAllocation& GPUModel::GetTextureBufferAllocation() const {
	return *texCoordsBufferAllocation;
}

const BaseIndexBufferAllocation& GPUModel::GetIndexBufferAllocation() const {
	return *indexBufferAllocation;
}

const uint32_t GPUModel::GetNumberOfIndices() const {
	return nVertices;
}