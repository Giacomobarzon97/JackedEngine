#include "StorageBufferDescriptorSet.h"

StorageBufferDescriptorSet::StorageBufferDescriptorSet(const Device& device, const StorageBufferDescriptorLayout& descriptorLayout, const StorageBufferDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const uint32_t elementSize, const uint32_t maxElements) :
	BaseDescriptorSet(device),
	storageBufferAllocation(allocationFactory.CreateStorageBufferAllocation(elementSize, maxElements))
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
	bufferInfo.buffer = storageBufferAllocation->GetBuffer();
	bufferInfo.offset = 0;
	bufferInfo.range = elementSize * maxElements;

	VkWriteDescriptorSet descriptorWrite{};

	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = descriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pBufferInfo = &bufferInfo;

	vkUpdateDescriptorSets(device.GetLogicalDevice(), 1, &descriptorWrite, 0, nullptr);
}

StorageBufferDescriptorSet::~StorageBufferDescriptorSet(){
	delete storageBufferAllocation;
}

void StorageBufferDescriptorSet::UpdateBuffer(const void* data, const uint32_t nElements) const {
	storageBufferAllocation->UpdateBuffer(data, nElements);
}