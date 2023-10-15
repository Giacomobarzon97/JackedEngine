#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define NOMINMAX
#include <optional>
#include <algorithm>
#include <set>
#include <array>
#include <vector>
#include <stdexcept>
#include <vulkan/vulkan.h>
#ifdef _DEBUG
#include <iostream>
#endif
#include "Windows/BaseWindow.h"

class Device {
public:
	Device(const BaseWindow& window);
	Device(Device &) = delete;
	~Device();
	Device &operator=(Device &) = delete;

	const VkDevice& GetLogicalDevice() const;
	const VkPhysicalDevice& GetPhysicalDevice() const;
	const VkInstance& GetInstance() const;
	const VkQueue& GetGraphicsQueue() const;
	const VkQueue& GetPresentQueue() const;
	const VkSwapchainKHR& GetSwapChain() const;
	const VkExtent2D& GetSwapChainExtent() const;
	const VkFramebuffer& GetSwapChainFramebuffer(const uint32_t i) const;
	const VkRenderPass& GetRenderPass() const;
	const VkCommandPool& GetCommandPool() const;
	const VkPhysicalDeviceProperties& GetDeviceProperties() const;
	const uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
	const std::vector<VkClearValue> GetClearValues() const;
	const VkSampleCountFlagBits GetNumberOfMSAASamples() const;

	void RecreateSwapChain();

#ifdef _DEBUG
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
#endif

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

	const BaseWindow& window;
	VkInstance instance;
	VkSurfaceKHR surface;
	VkDebugUtilsMessengerEXT debugMessenger;
#ifdef _DEBUG
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
#endif
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
#ifdef _DEBUG
		,VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME
#endif
	};
	const std::vector<const char*> instanceExtensions = {
#ifdef _DEBUG
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
	};

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
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceMemoryProperties memProperties;
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
	VkSampleCountFlagBits msaaSamples;
	VkImage colorImage;
	VkDeviceMemory colorImageMemory;
	VkImageView colorImageView;

	void createInstance();
#ifdef _DEBUG
	bool checkValidationLayerSupport();
	void setupDebugMessenger();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
#endif
	void createWindowSurface();
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
	void cleanupSwapChain();
	void createCommandPool();
	void createDepthResources();
	void createColorResources();
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkSampleCountFlagBits getMaxUsableSampleCount();
};