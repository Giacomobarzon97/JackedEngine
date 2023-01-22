#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Rendering/Instance.h"

class BaseWindowSurface {
public:
	virtual ~BaseWindowSurface() = 0;
	VkSurfaceKHR getVkSurface();

protected:
	Instance* instance;
	VkSurfaceKHR surface;
};
