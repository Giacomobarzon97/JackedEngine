#include "UniformDescriptorSet.h"

UniformDescriptorSet::UniformDescriptorSet(const Device& device, const UniformDescriptorLayout& descriptorLayout, const UniformDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const uint32_t uniformSize) :
	BaseDescriptorSet(device),
	uniformAllocation(allocationFactory.CreateUniformAllocation(uniformSize))
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
	bufferInfo.buffer = uniformAllocation->GetBuffer();
	bufferInfo.offset = 0;
	bufferInfo.range = uniformSize;

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

UniformDescriptorSet::~UniformDescriptorSet(){
	delete uniformAllocation;
}

void UniformDescriptorSet::UpdateUniform(const void* data) const {

	uniformAllocation->UpdateBuffer(data);
}