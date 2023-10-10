#include "ImageDescriptorSet.h"

ImageDescriptorSet::ImageDescriptorSet(const Device& device, const ImageDescriptorLayout& descriptorLayout, const ImageDescriptorPool& descriptorPool, const BaseAllocationFactory& allocationFactory, const GPUBaseImage& image, const BaseSampler& sampler) :
	BaseDescriptorSet(device),
	image(image),
	sampler(sampler)
{
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool.GetDescriptorPool();
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = &descriptorLayout.GetDescriptorLayout();
	if (vkAllocateDescriptorSets(device.GetLogicalDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	VkDescriptorImageInfo imageInfo{};
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	imageInfo.imageView = image.GetImageView();
	imageInfo.sampler = sampler.GetSampler();

	VkWriteDescriptorSet descriptorWrite{};

	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = descriptorSet;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pImageInfo = &imageInfo;

	vkUpdateDescriptorSets(device.GetLogicalDevice(), 1, &descriptorWrite, 0, nullptr);
}

ImageDescriptorSet::~ImageDescriptorSet() {}