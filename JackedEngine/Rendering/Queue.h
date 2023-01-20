#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <set>
#include <iostream>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isValid() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}

};

class Queue {
public:
	Queue(VkInstance* vkInstance, VkSurfaceKHR* surface);
	~Queue();

	Queue(const Queue &) = delete;
	Queue &operator=(const Queue &) = delete;

private:
	VkInstance* vkInstance;
	VkSurfaceKHR* surface;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	const std::vector<const char*> validationLayers = { 
		"VK_LAYER_KHRONOS_validation" 
	};
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
#ifdef _DEBUG
	const bool enableValidationLayers = true;
#else
	const bool enableValidationLayers = false;
#endif


	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void createLogicalDevice();

};