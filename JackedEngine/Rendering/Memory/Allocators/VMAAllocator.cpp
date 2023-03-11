#include "VMAAllocator.h"
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

VMAAllocator::VMAAllocator(const Device& device) :
	BaseAllocator(device)
{
	VmaAllocatorCreateInfo allocatorInfo = {};
	allocatorInfo.physicalDevice = device.GetPhysicalDevice();
	allocatorInfo.device = device.GetLogicalDevice();
	allocatorInfo.instance = device.GetInstance();

	if (vmaCreateAllocator(&allocatorInfo, &allocator) != VK_SUCCESS) {
		throw std::runtime_error("failed to vma allocator!");
	}
}

VMAAllocator::~VMAAllocator() {
	vmaDestroyAllocator(allocator);
}

void VMAAllocator::CreateBuffer(VkBuffer& buffer, VmaAllocation& allocation, const VkDeviceSize bufferSize, const VkBufferUsageFlags usage, const VkMemoryPropertyFlags properties) const {
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = bufferSize;
	bufferInfo.usage = usage;

	VmaAllocationCreateInfo vmaallocInfo = {};
	vmaallocInfo.requiredFlags = properties;

	if (vmaCreateBuffer(allocator, &bufferInfo, &vmaallocInfo, &buffer, &allocation, nullptr)!= VK_SUCCESS) {
		throw std::runtime_error("failed to create texture buffer!");
	}
}

void VMAAllocator::MapMemory(VmaAllocation& allocation, void*& memLoc) const {
	vmaMapMemory(allocator, allocation, &memLoc);
}

void VMAAllocator::UnMapMemory(VmaAllocation& allocation) const {
	vmaUnmapMemory(allocator, allocation);
}

void VMAAllocator::DestroyBuffer(VkBuffer& buffer, VmaAllocation allocation) const {
	vmaDestroyBuffer(allocator, buffer, allocation);
}

const VkDeviceSize VMAAllocator::GetAvailableMemory() const {
	VmaBudget budgetInfo;
	vmaGetHeapBudgets(allocator, &budgetInfo);
	return budgetInfo.budget;
}

void VMAAllocator::CreateImage(VkImage& image, VmaAllocation& allocation, const uint32_t width, const uint32_t height, const VkFormat format, const VkImageTiling tiling, const VkImageUsageFlags usage, const VkMemoryPropertyFlags properties) const {
	VkImageCreateInfo imageInfo{};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = width;
	imageInfo.extent.height = height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = format;
	imageInfo.tiling = tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = usage;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	VmaAllocationCreateInfo allocInfo{};
	allocInfo.requiredFlags = properties;

	if (vmaCreateImage(allocator, &imageInfo, &allocInfo, &image, &allocation, nullptr) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture image!");
	}
}

void VMAAllocator::DestroyImage(VkImage& image, VmaAllocation& allocation) const {
	vmaDestroyImage(allocator, image, allocation);
}
