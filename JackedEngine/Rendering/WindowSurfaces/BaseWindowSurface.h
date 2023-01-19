#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class BaseWindowSurface {
public:
	virtual ~BaseWindowSurface() = 0;
protected:
	VkInstance* vkInstance;
	VkSurfaceKHR surface;
};
