#include "CPUModel.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

CPUModel::CPUModel(const std::string objPath){
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objPath.c_str())) {
        throw std::runtime_error(warn + err);
    }
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            CPUVertex vertex = CPUVertex(
                {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2],
                    1
                },
                {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                }
            );
            vertices.push_back(vertex);
            indices.push_back(static_cast<uint32_t>(indices.size()));
        }
    }
}

const size_t CPUModel::GetVertexSize() const {
	return sizeof(CPUVertex);
}

const size_t CPUModel::GetIndexSize() const {
	return sizeof(uint32_t);
}

const uint32_t CPUModel::GetNumberOfVertices() const {
	return static_cast<uint32_t>(vertices.size());
}

const uint32_t CPUModel::GetNumberOfIndices() const {
    return static_cast<uint32_t>(indices.size());
}

const void* CPUModel::GetVertexData() const {
	return vertices.data();
}

const void* CPUModel::GetIndexData() const {
	return indices.data();
}

const VkIndexType CPUModel::GetIndexType() {
    return VK_INDEX_TYPE_UINT32;
}