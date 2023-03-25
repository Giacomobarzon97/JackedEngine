#include "GPUTexturedModel.h"

GPUTexturedModel::GPUTexturedModel(const BaseAllocationFactory& allocationFactory, const CPUModel& model) : 
	GPUBaseModel(allocationFactory, model)
{
	texCoordsBufferAllocation = allocationFactory.CreateVertexBufferAllocation(
		model.GetTextureVertexData(),
		sizeof(CPUTextureVertex) * model.GetNumberOfVertices()
	);
}

GPUTexturedModel::~GPUTexturedModel() {
	delete texCoordsBufferAllocation;
}

const BaseVertexBufferAllocation& GPUTexturedModel::GetTextureBufferAllocation() const {
	return *texCoordsBufferAllocation;
}