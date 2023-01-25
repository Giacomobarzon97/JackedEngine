#pragma once

#define NOMINMAX
#include <algorithm>
#include "Rendering/Device.h"
#include "Rendering/Instance.h"
#include "Windows/BaseWindow.h"

class SwapChain {
public:
	SwapChain(Instance* instance, Device* device, BaseWindow* window);
	SwapChain(SwapChain &) = delete;
	~SwapChain();
	SwapChain &operator=(SwapChain &) = delete;

	VkExtent2D GetSwapChainExtent();
	VkFormat GetSwapChainImageFormat();
	VkRenderPass* GetRenderPass();

private:
	Instance* instance;
	Device* device;
	BaseWindow* window;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	VkRenderPass renderPass;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createRenderPass();
	void createFrameBuffers();
};