#include "GPUModel.h"

GPUModel::GPUModel(const BaseAllocationFactory& allocationFactory, const CPUBaseModel& model)
{
	ModelData data = model.GetModelData();

	bufferAllocations.resize(data.vertexData.size());

	for (unsigned int i = 0; i < data.vertexData.size(); i++) {
		bufferAllocations[i] = allocationFactory.CreateVertexBufferAllocation(
			data.vertexData[i].data,
			data.vertexData[i].size
		);
	}

	indexBufferAllocation = allocationFactory.CreateIndexBufferAllocation(
		data.indexData.data,
		data.indexData.size
	);

	nVertices = data.numberOfIndices;
}

GPUModel::~GPUModel() {
	for (int i = 0; i < bufferAllocations.size(); i++) {
		delete bufferAllocations[i];
	}

	delete indexBufferAllocation;
}

const std::vector<VkBuffer> GPUModel::GetBuffers() const{
	std::vector<VkBuffer> buffers;
	buffers.resize(bufferAllocations.size());
	for (int i = 0; i < bufferAllocations.size(); i++) {
		buffers[i] = bufferAllocations[i]->GetBuffer();
	}
	return buffers;
}

const BaseIndexBufferAllocation& GPUModel::GetIndexBufferAllocation() const {
	return *indexBufferAllocation;
}

const uint32_t GPUModel::GetNumberOfIndices() const {
	return nVertices;
}

/*
	TODO: This could be fixed to dynamically detect the size of the indices at run time based on the CPUModel received in input
	and return the correct VkIndexType
*/
const VkIndexType GPUModel::GetIndexType() {
	return VK_INDEX_TYPE_UINT32;
}
