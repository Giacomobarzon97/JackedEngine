#pragma once

#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <string>
#include "BaseWindow.h"

class GLFWWindow : public BaseWindow
{
public:
	GLFWWindow(const uint32_t w, const uint32_t h, const std::string windowName);
	~GLFWWindow();

	GLFWWindow(const GLFWWindow &) = delete;
	GLFWWindow &operator=(const GLFWWindow &) = delete;

	void InitiWindowSurface(Instance* instance, VkSurfaceKHR* windowSurface);

	bool ShouldClose();
	void PollEvents();

	HWND GetWindowHandle();
	const char** GetRequiredExtensions(uint32_t* extensionCount);

private: 
	GLFWwindow *window;
};

