#pragma once

#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <stdexcept>
#include "Rendering\WindowSurfaces\BaseWindowSurface.h"

class GLFWWindowSurface : public BaseWindowSurface{
public:
	GLFWWindowSurface(Instance* instance, GLFWwindow* win32Window);
	virtual ~GLFWWindowSurface();
private:
	GLFWwindow* window;
};