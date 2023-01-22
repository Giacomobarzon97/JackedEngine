#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class Instance 
{
public:
	Instance(std::string appName, std::vector<const char*> extensions);
	Instance(const Instance &) = delete;
	Instance(Instance &) = delete;
	~Instance();

	Instance &operator=(const Instance &) = delete;
	Instance &operator=(Instance &) = delete;

	VkInstance* GetVkInstance();

private:
	VkInstance vkInstance;
	const std::vector<const char*> validationLayers = { 
		"VK_LAYER_KHRONOS_validation" 
	};
#ifdef _DEBUG
	const bool enableValidationLayers = true;
#else
	const bool enableValidationLayers = false;
#endif

	bool checkValidationLayerSupport();
};