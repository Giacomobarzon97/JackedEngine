#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "Window.h"

class JackedEngine {
public:
	JackedEngine();
	~JackedEngine();

	JackedEngine(const JackedEngine &) = delete;
	JackedEngine &operator=(const JackedEngine &) = delete;

private:
	static const std::string APP_NAME;
	static const uint32_t  WINDOW_WIDTH;
	static const uint32_t  WINDOW_HEIGHT;

	Window window;
	VkInstance vkInstance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
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
	void mainLoop();
};
