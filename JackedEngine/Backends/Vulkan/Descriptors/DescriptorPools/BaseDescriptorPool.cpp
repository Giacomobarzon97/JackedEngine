#include "BaseDescriptorPool.h"

BaseDescriptorPool::BaseDescriptorPool(const Device& device) :
	device(device)
{}

BaseDescriptorPool::~BaseDescriptorPool() {
	vkDestroyDescriptorPool(device.GetLogicalDevice(), descriptorPool, nullptr);
}

const VkDescriptorPool& BaseDescriptorPool::GetDescriptorPool() const {
	return descriptorPool;
}