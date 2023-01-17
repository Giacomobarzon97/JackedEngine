#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

class Queue {
public:
	Queue(VkInstance* vkInstance);

private:
	VkInstance* vkInstance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	void pickPhysicalDevice();
};