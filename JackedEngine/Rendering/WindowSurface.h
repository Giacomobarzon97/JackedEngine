#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <Windows.h>
#include <vulkan/vulkan.h>
#include "Rendering/Instance.h"
#include "Windows/BaseWindow.h"

class WindowSurface {

public:
	WindowSurface(Instance* instance, BaseWindow* window);
	WindowSurface(WindowSurface &) = delete;
	~WindowSurface();
	WindowSurface &operator=(WindowSurface &) = delete;

	VkSurfaceKHR* GetVkSurface();

private:
	VkSurfaceKHR surface;
	Instance* instance;
	BaseWindow* window;
};
