#include "VMACubemapBufferAllocation.h"

VMACubemapBufferAllocation::VMACubemapBufferAllocation(const VMAAllocator& allocator, const void* frontFaceData, const void* backFaceData, const void* upFaceData, const void* downFaceData, const void* rightFaceData, const void* leftFaceData, const int width, const int height) :
	allocator(allocator)
{
	VkBuffer stagingBuffer;
	VmaAllocation stagingAllocation;
	void* stagingMemLoc;
	VkDeviceSize layerSize = width * height * 4;
	VkDeviceSize cubeMapSize = layerSize * 6;

	allocator.CreateBuffer(stagingBuffer, stagingAllocation, cubeMapSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	allocator.MapMemory(stagingAllocation, stagingMemLoc);
	memcpy(static_cast<char*>(stagingMemLoc), frontFaceData, layerSize);
	memcpy(static_cast<char*>(stagingMemLoc) + layerSize, backFaceData, layerSize);
	memcpy(static_cast<char*>(stagingMemLoc) + (layerSize * 2), upFaceData, layerSize);
	memcpy(static_cast<char*>(stagingMemLoc) + (layerSize * 3), downFaceData, layerSize);
	memcpy(static_cast<char*>(stagingMemLoc) + (layerSize * 4), rightFaceData, layerSize);
	memcpy(static_cast<char*>(stagingMemLoc) + (layerSize * 5), leftFaceData, layerSize);

	allocator.UnMapMemory(stagingAllocation);
	allocator.CreateImage(image, allocation, width, height, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 6, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT);
	allocator.TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 6);
	allocator.CopyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(width), static_cast<uint32_t>(height), 6);
	allocator.TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, 6);
	allocator.DestroyBuffer(stagingBuffer, stagingAllocation);

	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
	viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 6;
	if (vkCreateImageView(allocator.GetDevice().GetLogicalDevice(), &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image view!");
	}
}

VMACubemapBufferAllocation::~VMACubemapBufferAllocation() {
	vkDestroyImageView(allocator.GetDevice().GetLogicalDevice(), imageView, nullptr);
	allocator.DestroyImage(image, allocation);
}

