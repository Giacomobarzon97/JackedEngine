#include "BaseDescriptorPool.h"

BaseDescriptorPool::BaseDescriptorPool(const Device* const device) :
	device(device)
{}

BaseDescriptorPool::~BaseDescriptorPool() {
	vkDestroyDescriptorPool(*device->GetLogicalDevice(), descriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(*device->GetLogicalDevice(), descriptorSetLayout, nullptr);
}

const VkDescriptorSetLayout* const BaseDescriptorPool::GetDescriptorSetLayout() const {
	return &descriptorSetLayout;
}

const VkDescriptorPool* const BaseDescriptorPool::GetDescriptorPool() const {
	return &descriptorPool;
}