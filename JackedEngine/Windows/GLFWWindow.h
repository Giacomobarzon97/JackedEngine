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
	GLFWWindow(GLFWWindow &) = delete;
	~GLFWWindow();
	GLFWWindow &operator=(GLFWWindow &) = delete;

	virtual void InitiWindowSurface(VkInstance* instance, VkSurfaceKHR* windowSurface) override;
	virtual bool ShouldClose() override;
	virtual void PollEvents() override;
	virtual HWND GetWindowHandle() override;
	virtual const char** GetRequiredExtensions(uint32_t* extensionCount) override;
	virtual void GetFrameBufferSize(int* width, int* height) override;
	virtual void SetBufferResizeCallback(void* buffer, void(*func)(void*)) override;
	virtual void WaitWhileMinimized() override;

private: 
	GLFWwindow *window;
	static void (*bufferCallback)(void*);

	static void BufferResizeCallback(GLFWwindow* window, int width, int height);
};

