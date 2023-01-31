#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <set>
#include <iostream>
#include <optional>
#include "Rendering/Instance.h"

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isValid() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;

	bool isValid() {
		return !formats.empty() && !presentModes.empty();
	}
};

class Device {
public:
	Device(Instance* instance);
	Device(Device &) = delete;
	~Device();
	Device &operator=(Device &) = delete;

	VkDevice* GetLogicalDevice();
	VkPhysicalDevice* GetPhysicalDevice();
	VkQueue* GetGraphicsQueue();
	VkQueue* GetPresentQueue();
	SwapChainSupportDetails GetSwapChainSupportDetails();
	QueueFamilyIndices GetQueueFamilyIndices();


private:
	Instance* instance;
	VkPhysicalDevice physicalDevice;
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
	SwapChainSupportDetails findSwapChainSupport(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void createLogicalDevice();
};