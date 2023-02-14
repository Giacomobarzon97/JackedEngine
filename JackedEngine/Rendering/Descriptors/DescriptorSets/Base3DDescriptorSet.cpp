#include "Base3DDescriptorSet.h"

Base3DDescriptorSet::Base3DDescriptorSet(const Device* const device, const Base3DDescriptorPool* const descriptorPool) :
	BaseDescriptorSet(device),
	mvpUniform(new UniformBuffer(device))
{
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = *descriptorPool->GetDescriptorPool();
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = descriptorPool->GetDescriptorSetLayout();
	if (vkAllocateDescriptorSets(*device->GetLogicalDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	VkDescriptorBufferInfo bufferInfo{};
	bufferInfo.buffer = *mvpUniform->GetUniformBuffer();
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

Base3DDescriptorSet::~Base3DDescriptorSet(){
	delete mvpUniform;
}

void Base3DDescriptorSet::UpdateDescriptorSet() const {
	mvpUniform->UpdateUniformBuffer();
}