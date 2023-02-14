#include "UniformBuffer.h"

std::chrono::steady_clock::time_point UniformBuffer::startTime = std::chrono::high_resolution_clock::now();

UniformBuffer::UniformBuffer(const Device* const device) :
	BaseBuffer(device)
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);
	createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);
	vkMapMemory(*device->GetLogicalDevice(), uniformBufferMemory, 0, bufferSize, 0, &uniformBufferMapped);
}

UniformBuffer::~UniformBuffer() {
	vkDestroyBuffer(*device->GetLogicalDevice(), uniformBuffer, nullptr);
	vkFreeMemory(*device->GetLogicalDevice(), uniformBufferMemory, nullptr);
}

void UniformBuffer::UpdateUniformBuffer() const{
	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	UniformBufferObject ubo{};
	ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	VkExtent2D extent = *device->GetSwapChainExtent();
	ubo.proj = glm::perspective(glm::radians(45.0f), extent.width / (float)extent.height, 0.1f, 10.0f);
	ubo.proj[1][1] *= -1;
	memcpy(uniformBufferMapped, &ubo, sizeof(ubo));
}

const VkBuffer* const UniformBuffer::GetUniformBuffer() const{
	return &uniformBuffer;
}
