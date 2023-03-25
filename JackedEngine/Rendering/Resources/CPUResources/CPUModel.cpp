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

const uint32_t CPUModel::GetNumberOfVertices() const {
	return static_cast<uint32_t>(positions.size());
}

const uint32_t CPUModel::GetNumberOfIndices() const {
    return static_cast<uint32_t>(indices.size());
}

const CPUPositionVertex* CPUModel::GetPositionVertexData() const {
    return positions.data();
}

const CPUTextureVertex* CPUModel::GetTextureVertexData() const {
    return texCoords.data();
}

const uint32_t* CPUModel::GetIndexData() const {
	return indices.data();
}

const VkIndexType CPUModel::GetIndexType() {
    return VK_INDEX_TYPE_UINT32;
}

const uint32_t CPUModel::GetIndexSize() {
    return sizeof(uint32_t);
}