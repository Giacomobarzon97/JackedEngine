#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <set>
#include <iostream>
#include <optional>
#include "Rendering/WindowSurface.h"
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
	Device(Instance* instance, WindowSurface* surface);
	Device(const Device &) = delete;
	Device(Device &) = delete;
	~Device();

	Device &operator=(const Device &) = delete;
	Device &operator=(Device &) = delete;

private:
	Instance* instance;
	WindowSurface* surface;
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
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	void createLogicalDevice();
};