#include "FrameDescriptorSet.h"

FrameDescriptorSet::FrameDescriptorSet(const Device& device, const FrameDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory) :
	BaseDescriptorSet(device),
	projectionViewUniform(allocationFactory.CreateUniformBufferAllocation(sizeof(UniformBufferObject)))
{
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool.GetDescriptorPool();
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = &descriptorPool.GetDescriptorSetLayout();
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

void FrameDescriptorSet::UpdateProjectionViewMatrix(glm::mat4 projectionView) const {
	UniformBufferObject ubo{};
	ubo.projectionView = projectionView;
	projectionViewUniform->UpdateBuffer(&ubo);
}