#pragma once

#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <string>
#include <optional>

class Window
{
public:
	Window(const uint32_t w, const uint32_t h, const std::string windowName);
	~Window();

	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;

	bool ShouldClose();
	void PollEvents();

	GLFWwindow* getGLFWWindow();

	static const char** GetRequiredExtensions(uint32_t* extensionCount);

private: 
	const uint32_t width;
	const uint32_t height;
	const std::string windowName;
	GLFWwindow *window;
	std::optional<VkInstance*> vkInstance;
	VkSurfaceKHR surface;
};

