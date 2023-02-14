#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(const Device& device, const size_t bufferSize) :
	BaseBuffer(device),
	bufferSize(bufferSize)
{
	createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);
	vkMapMemory(device.GetLogicalDevice(), uniformBufferMemory, 0, bufferSize, 0, &uniformBufferMapped);
}

UniformBuffer::~UniformBuffer() {
	vkDestroyBuffer(device.GetLogicalDevice(), uniformBuffer, nullptr);
	vkFreeMemory(device.GetLogicalDevice(), uniformBufferMemory, nullptr);
}

void UniformBuffer::UpdateUniformBuffer(const void * data) const{
	memcpy(uniformBufferMapped, data, bufferSize);
}

const VkBuffer& UniformBuffer::GetUniformBuffer() const{
	return uniformBuffer;
}
