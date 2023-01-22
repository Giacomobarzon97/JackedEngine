#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <Windows.h>
#include <vulkan/vulkan.h>
#include "Rendering/Instance.h"
#include "Windows/BaseWindow.h"

class WindowSurface {

public:
	WindowSurface(Instance* instance, BaseWindow* window);
	WindowSurface(const WindowSurface &) = delete;
	WindowSurface(WindowSurface &) = delete;
	~WindowSurface();

	WindowSurface &operator=(const WindowSurface &) = delete;
	WindowSurface &operator=(WindowSurface &) = delete;

	VkSurfaceKHR* getVkSurface();

private:
	Instance* instance;
	VkSurfaceKHR surface;
};
