#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

class Instance 
{
public:
	Instance(std::string appName, std::vector<const char*> extensions);
	Instance(Instance &) = delete;
	~Instance();
	Instance &operator=(Instance &) = delete;

	VkInstance* GetVkInstance();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

private:
	VkInstance vkInstance;
	VkDebugUtilsMessengerEXT debugMessenger;
	const std::vector<const char*> validationLayers = { 
		"VK_LAYER_KHRONOS_validation" 
	};
#ifdef _DEBUG
	const bool enableValidationLayers = true;
#else
	const bool enableValidationLayers = false;
#endif

	void setupDebugMessenger();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	bool checkValidationLayerSupport();

};