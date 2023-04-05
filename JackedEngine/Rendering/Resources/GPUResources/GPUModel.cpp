#include "GPUModel.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

GPUModel::GPUModel(const BaseAllocationFactory& allocationFactory, const std::vector<uint32_t>& indices, const std::vector<CPUPositionVertex>& positions) {
	bufferAllocations.resize(1);
	bufferAllocations[0] = allocationFactory.CreateVertexBufferAllocation(
		positions.data(),
		sizeof(CPUPositionVertex) * positions.size()
	);
	indexBufferAllocation = allocationFactory.CreateIndexBufferAllocation(
		indices.data(),
		sizeof(uint32_t) * indices.size()
	);
	nVertices = static_cast<uint32_t>(indices.size());
}

GPUModel::GPUModel(const BaseAllocationFactory& allocationFactory, const std::vector<uint32_t>& indices, const std::vector<CPUTextureVertex>& texCoords) {
	bufferAllocations.resize(1);
	bufferAllocations[0] = allocationFactory.CreateVertexBufferAllocation(
		texCoords.data(),
		sizeof(CPUTextureVertex) * texCoords.size()
	);
	indexBufferAllocation = allocationFactory.CreateIndexBufferAllocation(
		indices.data(),
		sizeof(uint32_t) * indices.size()
	);
	nVertices = static_cast<uint32_t>(indices.size());
}

GPUModel::GPUModel(const BaseAllocationFactory& allocationFactory, const std::vector<uint32_t>& indices, const std::vector<CPUPositionVertex>& positions, const std::vector<CPUTextureVertex>& texCoords) {
	bufferAllocations.resize(1);
	bufferAllocations[0] = allocationFactory.CreateVertexBufferAllocation(
		positions.data(),
		sizeof(CPUPositionVertex) * positions.size()
	);
	bufferAllocations[1] = allocationFactory.CreateVertexBufferAllocation(
		texCoords.data(),
		sizeof(CPUTextureVertex) * texCoords.size()
	);
	indexBufferAllocation = allocationFactory.CreateIndexBufferAllocation(
		indices.data(),
		sizeof(uint32_t) * indices.size()
	);
	nVertices = static_cast<uint32_t>(indices.size());
}

GPUModel::GPUModel(const BaseAllocationFactory& allocationFactory, const std::string objPath)
{
	std::vector<CPUPositionVertex> positions;
	std::vector<CPUTextureVertex> texCoords;
	std::vector<uint32_t> indices;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objPath.c_str())) {
		throw std::runtime_error(warn + err);
	}
	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			positions.push_back(
				CPUPositionVertex({
						attrib.vertices[3 * index.vertex_index + 0],
						attrib.vertices[3 * index.vertex_index + 1],
						attrib.vertices[3 * index.vertex_index + 2],
						1
					})
			);
			texCoords.push_back(
				CPUTextureVertex({
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
					})
			);

			indices.push_back(static_cast<uint32_t>(indices.size()));
		}
	}

	bufferAllocations.resize(2);

	bufferAllocations[0] = allocationFactory.CreateVertexBufferAllocation(
		positions.data(),
		sizeof(CPUPositionVertex) * positions.size()
	);
	bufferAllocations[1] = allocationFactory.CreateVertexBufferAllocation(
		texCoords.data(),
		sizeof(CPUTextureVertex) * texCoords.size()
	);
	indexBufferAllocation = allocationFactory.CreateIndexBufferAllocation(
		indices.data(),
		sizeof(uint32_t) * indices.size()
	);

	nVertices = static_cast<uint32_t>(indices.size());
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

const VkIndexType GPUModel::GetIndexType() {
	return VK_INDEX_TYPE_UINT32;
}
