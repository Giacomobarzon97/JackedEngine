#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <iostream>
class Window {
public:
	Window(int w, int h, std::string name);
	~Window();

	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;

private:
	const int width;
	const int height;
	std::string windowName;
	GLFWwindow *window;
	VkInstance vkInstance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
	#ifdef _DEBUG
		const bool enableValidationLayers = true;
	#else
		const bool enableValidationLayers = false;
	#endif

	void init();
	void initGLFW();
	void initVKInstance();
	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void printAvailableExtensions();
	void initPhysicalDevice();
	bool isDeviceSuitable(const VkPhysicalDevice device);
	void mainLoop();
};
