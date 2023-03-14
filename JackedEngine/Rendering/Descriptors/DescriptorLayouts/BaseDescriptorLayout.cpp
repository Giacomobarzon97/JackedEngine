#include "BaseDescriptorLayout.h"


BaseDescriptorLayout::BaseDescriptorLayout(const Device& device) :
	device(device)
{}

BaseDescriptorLayout::~BaseDescriptorLayout() {
	vkDestroyDescriptorSetLayout(device.GetLogicalDevice(), descriptorSetLayout, nullptr);
}

const VkDescriptorSetLayout& BaseDescriptorLayout::GetDescriptorLayout() const {
	return descriptorSetLayout;
}