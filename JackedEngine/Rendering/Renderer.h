#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
#include "../Window.h"

class Renderer 
{
public:
	Renderer();
	~Renderer();

	Renderer(const Renderer &) = delete;
	Renderer &operator=(const Renderer &) = delete;

private:
	std::string appName;
	VkInstance vkInstance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
#ifdef _DEBUG
	const bool enableValidationLayers = true;
#else
	const bool enableValidationLayers = false;
#endif

	void initVKInstance();
	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void printAvailableExtensions();
	void initPhysicalDevice();
	bool isDeviceSuitable(const VkPhysicalDevice device);
};