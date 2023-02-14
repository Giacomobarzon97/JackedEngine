#pragma once
#include <vulkan/vulkan.h>
#include<vector>
#include "Rendering/Buffers/BaseBuffer.h"
#include "Rendering/Device.h"
#include "Logic/Vertex.h"

class VertexBuffer : public BaseBuffer{
public:
	VertexBuffer(const Device& device);
	VertexBuffer(VertexBuffer&) = delete;
	virtual ~VertexBuffer() override;

	VertexBuffer &operator=(VertexBuffer &) = delete;

	const VkBuffer& GetVertexBuffer() const;
	const VkBuffer& GetIndexBuffer() const;
	const uint32_t GetIndicesNumber() const;

private:
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	const std::vector<Vertex> vertices = {
		{{-0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
		{{0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
		{{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
		{{-0.5f, 0.5f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
	};

	const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
	};
};