#include "VMAImage2DAllocation.h"

VMAImage2DAllocation::VMAImage2DAllocation(const VMAAllocator& allocator, const void* data, const int width, const int height) :
	allocator(allocator)
{
	VkBuffer stagingBuffer;
	VmaAllocation stagingAllocation;
	void* stagingMemLoc;
	VkDeviceSize totalSize = width * height * 4;

	allocator.CreateBuffer(stagingBuffer, stagingAllocation, totalSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	allocator.MapMemory(stagingAllocation, stagingMemLoc);
	memcpy(static_cast<char*>(stagingMemLoc), data, totalSize);
	allocator.UnMapMemory(stagingAllocation);
	allocator.CreateImage(image, allocation, width, height, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 1, 0);
	allocator.TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1);
	allocator.CopyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(width), static_cast<uint32_t>(height), 1);
	allocator.TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, 1);
	allocator.DestroyBuffer(stagingBuffer, stagingAllocation);


	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;
	if (vkCreateImageView(allocator.GetDevice().GetLogicalDevice(), &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image view!");
	}
}

VMAImage2DAllocation::~VMAImage2DAllocation() {
	vkDestroyImageView(allocator.GetDevice().GetLogicalDevice(), imageView, nullptr);
	allocator.DestroyImage(image, allocation);
}