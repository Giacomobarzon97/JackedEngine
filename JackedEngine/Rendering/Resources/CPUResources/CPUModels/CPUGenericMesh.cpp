#include "CPUGenericMesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

CPUGenericMesh::CPUGenericMesh(const std::string objPath, const bool includePositions, const bool includeTexcoords) :
	objPath(objPath),
	includePositions(includePositions),
	includeTexcoords(includeTexcoords)
{}


/*
	TODO: This method could be moved to CPUBaseModel
*/
void CPUGenericMesh::LoadData() {
	positions.clear();
	texCoords.clear();
	indices.clear();

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
}

const ModelData CPUGenericMesh::GetModelData() const {
	if (indices.size() == 0) {
		throw std::runtime_error("No data has been loaded, call the LoadData() Method First");
	}

	ModelData data{};

	if (includePositions) {
		data.vertexData.push_back(
			BufferData{
				positions.data(),
				static_cast<uint32_t>(sizeof(CPUPositionVertex) * positions.size())
			}
		);
	}

	if (includeTexcoords) {
		data.vertexData.push_back(
			BufferData{
				texCoords.data(),
				static_cast<uint32_t>(sizeof(CPUTextureVertex) * texCoords.size())
			}
		);
	}

	data.indexData.data = indices.data();
	data.indexData.size = sizeof(uint32_t) * static_cast<uint32_t>(indices.size());
	data.numberOfIndices = static_cast<uint32_t>(indices.size());

	return data;
}

const std::string& CPUGenericMesh::GetId() const {
	return objPath;
}