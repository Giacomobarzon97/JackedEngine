#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const Device& device, const Model& model) :
	BaseBuffer(device),
	model(model)
{
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	VkDeviceSize bufferSize = model.GetVertexSize() * model.GetNumberOfVertices();

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(device.GetLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, model.GetVertexData(), (size_t)bufferSize);
	vkUnmapMemory(device.GetLogicalDevice(), stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

	vkDestroyBuffer(device.GetLogicalDevice(), stagingBuffer, nullptr);
	vkFreeMemory(device.GetLogicalDevice(), stagingBufferMemory, nullptr);


	bufferSize = model.GetIndexSize() * model.GetNumberOfIndices();
	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	vkMapMemory(device.GetLogicalDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, model.GetIndexData(), (size_t)bufferSize);
	vkUnmapMemory(device.GetLogicalDevice(), stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	copyBuffer(stagingBuffer, indexBuffer, bufferSize);

	vkDestroyBuffer(device.GetLogicalDevice(), stagingBuffer, nullptr);
	vkFreeMemory(device.GetLogicalDevice(), stagingBufferMemory, nullptr);
}

VertexBuffer::~VertexBuffer() {
	vkDestroyBuffer(device.GetLogicalDevice(), indexBuffer, nullptr);
	vkFreeMemory(device.GetLogicalDevice(), indexBufferMemory, nullptr);
	vkDestroyBuffer(device.GetLogicalDevice(), vertexBuffer, nullptr);
	vkFreeMemory(device.GetLogicalDevice(), vertexBufferMemory, nullptr);
}

const VkBuffer& VertexBuffer::GetVertexBuffer() const {
	return vertexBuffer;
}

const VkBuffer& VertexBuffer::GetIndexBuffer() const {
	return indexBuffer;
}

const uint32_t VertexBuffer::GetIndicesNumber() const {
	return static_cast<uint32_t>(model.GetNumberOfIndices());
}