#include "FrameDescriptorSet.h"

FrameDescriptorSet::FrameDescriptorSet(const Device& device, const FrameDescriptorLayout& descriptorLayout, const FrameDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory) :
	BaseDescriptorSet(device),
	projectionViewUniform(allocationFactory.CreateUniformAllocation(sizeof(UniformBufferObject)))
{
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool.GetDescriptorPool();
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = &descriptorLayout.GetDescriptorLayout();
	if (vkAllocateDescriptorSets(device.GetLogicalDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	VkDescriptorBufferInfo bufferInfo{};
	bufferInfo.buffer = projectionViewUniform->GetBuffer();
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

	vkUpdateDescriptorSets(device.GetLogicalDevice(), 1, &descriptorWrite, 0, nullptr);
}

FrameDescriptorSet::~FrameDescriptorSet(){
	delete projectionViewUniform;
}

void FrameDescriptorSet::UpdateUBO(const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix) const {
	UniformBufferObject ubo{};
	ubo.viewMatrix = viewMatrix;
	ubo.projectionMatrix = projectionMatrix;
	projectionViewUniform->UpdateBuffer(&ubo);
}