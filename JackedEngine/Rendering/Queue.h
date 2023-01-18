#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool isValid() {
		return graphicsFamily.has_value();
	}

};

class Queue {
public:
	Queue(VkInstance* vkInstance);
	~Queue();

	Queue(const Queue &) = delete;
	Queue &operator=(const Queue &) = delete;

private:
	VkInstance* vkInstance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice;
	QueueFamilyIndices queueFamilyIndices;
	VkQueue graphicsQueue;
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
#ifdef _DEBUG
	const bool enableValidationLayers = true;
#else
	const bool enableValidationLayers = false;
#endif


	void pickPhysicalDevice();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	void createLogicalDevice();
};