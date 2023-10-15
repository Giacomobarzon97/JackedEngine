#include "StorageBufferDescriptorLayout.h"

StorageBufferDescriptorLayout::StorageBufferDescriptorLayout(const Device& device) :
	BaseDescriptorLayout(device)
{
	VkDescriptorSetLayoutBinding uboLayoutBinding{};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	uboLayoutBinding.pImmutableSamplers = nullptr;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_ALL;

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 1;
	layoutInfo.pBindings = &uboLayoutBinding;
	if (vkCreateDescriptorSetLayout(device.GetLogicalDevice(), &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}
