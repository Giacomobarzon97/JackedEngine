#include "VMAImageAllocation.h"

VMAImageAllocation::VMAImageAllocation(const VMAAllocator& allocator, const std::vector<const void*> data, const int width, const int height, VkImageViewType imageViewType, VkImageCreateFlags flags) :
	allocator(allocator)
{
	VkBuffer stagingBuffer;
	VmaAllocation stagingAllocation;
	void* stagingMemLoc;
	VkDeviceSize layerSize = width * height * 4;
	VkDeviceSize totalSize = layerSize * data.size();

	allocator.CreateBuffer(stagingBuffer, stagingAllocation, totalSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	allocator.MapMemory(stagingAllocation, stagingMemLoc);
	for (unsigned int i = 0; i < data.size(); i++) {
		memcpy(static_cast<char*>(stagingMemLoc) + (layerSize * i), data[i], layerSize);
	}
	allocator.UnMapMemory(stagingAllocation);
	allocator.CreateImage(image, allocation, width, height, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, static_cast<uint32_t>(data.size()), flags);
	allocator.TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<uint32_t>(data.size()));
	allocator.CopyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(width), static_cast<uint32_t>(height), static_cast<uint32_t>(data.size()));
	allocator.TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, static_cast<uint32_t>(data.size()));
	allocator.DestroyBuffer(stagingBuffer, stagingAllocation);


	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = imageViewType;
	viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = static_cast<uint32_t>(data.size());
	if (vkCreateImageView(allocator.GetDevice().GetLogicalDevice(), &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image view!");
	}
}

VMAImageAllocation::~VMAImageAllocation() {
	vkDestroyImageView(allocator.GetDevice().GetLogicalDevice(), imageView, nullptr);
	allocator.DestroyImage(image, allocation);
}