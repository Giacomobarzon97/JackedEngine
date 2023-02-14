#include "BaseDescriptorPool.h"

BaseDescriptorPool::BaseDescriptorPool(const Device& device) :
	device(device)
{}

BaseDescriptorPool::~BaseDescriptorPool() {
	vkDestroyDescriptorPool(device.GetLogicalDevice(), descriptorPool, nullptr);
	vkDestroyDescriptorSetLayout(device.GetLogicalDevice(), descriptorSetLayout, nullptr);
}

const VkDescriptorSetLayout& BaseDescriptorPool::GetDescriptorSetLayout() const {
	return descriptorSetLayout;
}

const VkDescriptorPool& BaseDescriptorPool::GetDescriptorPool() const {
	return descriptorPool;
}