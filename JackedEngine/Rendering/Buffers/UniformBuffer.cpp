#include "UniformBuffer.h"

std::chrono::steady_clock::time_point UniformBuffer::startTime = std::chrono::high_resolution_clock::now();

UniformBuffer::UniformBuffer(const Device* const device, const Pipeline* const pipeline) :
	BaseBuffer(device),
	pipeline(pipeline)
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);
	createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);
	vkMapMemory(*device->GetLogicalDevice(), uniformBufferMemory, 0, bufferSize, 0, &uniformBufferMapped);

	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = *pipeline->GetDescriptorPool();
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = pipeline->GetDescriptorSetLayout();
	if (vkAllocateDescriptorSets(*device->GetLogicalDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	VkDescriptorBufferInfo bufferInfo{};
	bufferInfo.buffer = uniformBuffer;
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(UniformBufferObject);
	VkWriteDescriptorSet descriptorWrite{};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = descriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pBufferInfo = &bufferInfo;
	descriptorWrite.pImageInfo = nullptr; // Optional
	descriptorWrite.pTexelBufferView = nullptr; // Optional
	vkUpdateDescriptorSets(*device->GetLogicalDevice(), 1, &descriptorWrite, 0, nullptr);
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

const VkDescriptorSet* const UniformBuffer::GetDescriptorSet() const {
	return &descriptorSet;
}
