#include "MaterialDescriptorPool.h"

MaterialDescriptorPool::MaterialDescriptorPool(const Device& device, int maxSets) :
	BaseDescriptorPool(device)
{
	VkDescriptorPoolSize poolSize;
	poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSize.descriptorCount = static_cast<uint32_t>(maxSets);

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = 1;
	poolInfo.pPoolSizes = &poolSize;
	poolInfo.maxSets = static_cast<uint32_t>(maxSets);

	if (vkCreateDescriptorPool(device.GetLogicalDevice(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}


MaterialDescriptorPool::~MaterialDescriptorPool() {}