#pragma once
#include <vulkan/vulkan.h>
#include<vector>
#include "Rendering/Device.h"
#include "Logic/Vertex.h"

class VertexBuffer {
public:
	VertexBuffer(Device* device, VkCommandPool* commandPool);
	VertexBuffer(VertexBuffer&) = delete;
	~VertexBuffer();

	VertexBuffer &operator=(VertexBuffer &) = delete;

	VkBuffer* GetVertexBuffer();

private:
	Device* device;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkCommandPool* commandPool;

	const std::vector<Vertex> vertices = {
		Vertex({0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}),
		Vertex({0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}),
		Vertex({-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f})
	};

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
};