#pragma once

#define NOMINMAX
#include <optional>
#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
#include <vulkan/vulkan.h>
#include "Windows/BaseWindow.h"

class Device {
public:
	Device(const BaseWindow* const window);
	Device(Device &) = delete;
	~Device();
	Device &operator=(Device &) = delete;

	const VkDevice* const GetLogicalDevice() const;
	const VkPhysicalDevice* const GetPhysicalDevice() const;
	const VkQueue* const GetGraphicsQueue() const;
	const VkQueue* const GetPresentQueue() const;
	const VkSwapchainKHR* const GetSwapChain() const;
	const VkExtent2D* const GetSwapChainExtent() const;
	const VkFramebuffer* const GetSwapChainFramebuffer(const uint32_t i) const;
	const VkRenderPass* const GetRenderPass() const;
	const VkCommandPool* const GetCommandPool() const;

	void RecreateSwapChain();


	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

private:
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

	const BaseWindow* const window;
	VkInstance instance;
	VkSurfaceKHR surface;
	VkDebugUtilsMessengerEXT debugMessenger;
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
	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	SwapChainSupportDetails swapChainSupport;
	QueueFamilyIndices queueFamilyIndices;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	VkRenderPass renderPass;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;

	void createInstance();
	bool checkValidationLayerSupport();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	void setupDebugMessenger();

	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	SwapChainSupportDetails findSwapChainSupport(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void createLogicalDevice();

	void createSwapChain();
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	void createImageViews();
	void createRenderPass();
	void createFrameBuffers();

	void createCommandPool();

	void cleanupSwapChain();

};