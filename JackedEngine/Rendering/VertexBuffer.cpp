#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Device* device) :
	device(device)
{
	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = sizeof(vertices[0]) * vertices.size();
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	if (vkCreateBuffer(*device->GetLogicalDevice(), &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create vertex buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(*device->GetLogicalDevice(), vertexBuffer, &memRequirements);
	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	if (vkAllocateMemory(*device->GetLogicalDevice(), &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate vertex buffer memory!");
	}
	vkBindBufferMemory(*device->GetLogicalDevice(), vertexBuffer, vertexBufferMemory, 0);

	void* data;
	vkMapMemory(*device->GetLogicalDevice(), vertexBufferMemory, 0, bufferInfo.size, 0, &data);
	memcpy(data, vertices.data(), (size_t)bufferInfo.size);
	vkUnmapMemory(*device->GetLogicalDevice(), vertexBufferMemory);

}

VertexBuffer::~VertexBuffer() {
	vkDestroyBuffer(*device->GetLogicalDevice(), vertexBuffer, nullptr);
	vkFreeMemory(*device->GetLogicalDevice(), vertexBufferMemory, nullptr);
}

uint32_t VertexBuffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(*device->GetPhysicalDevice(), &memProperties);
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}
	throw std::runtime_error("failed to find suitable memory type!");
}

VkBuffer* VertexBuffer::GetVertexBuffer() {
	return &vertexBuffer;
}