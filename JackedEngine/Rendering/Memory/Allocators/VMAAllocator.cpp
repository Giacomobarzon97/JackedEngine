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
	vmaCreateAllocator(&allocatorInfo, &allocator);
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

	vmaCreateBuffer(allocator, &bufferInfo, &vmaallocInfo, &buffer, &allocation, nullptr);
}

void VMAAllocator::MapMemory(VmaAllocation& allocation, const void* data, const VkDeviceSize dataSize) const{
	void* memLoc;
	vmaMapMemory(allocator, allocation, &memLoc);
	memcpy(memLoc, data, dataSize);
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