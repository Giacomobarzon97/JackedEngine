#pragma once

#define NOMINMAX
#include <algorithm>
#include "Rendering/Device.h"
#include "Rendering/WindowSurface.h"
#include "Windows/BaseWindow.h"

class SwapChain {
public:
	SwapChain(Device* device, BaseWindow* window, WindowSurface* windowSurface);
	~SwapChain();

private:
	WindowSurface* windowSurface;
	Device* device;
	BaseWindow* window;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
};