#include "GLFWWindow.h"

GLFWWindow::GLFWWindow(const uint32_t w, const uint32_t h, const std::string windowName) :
	BaseWindow(w, h, windowName)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

GLFWWindow::~GLFWWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool GLFWWindow::ShouldClose() {
	return glfwWindowShouldClose(window);
}

void GLFWWindow::PollEvents() {
	glfwPollEvents();
}

const char** GLFWWindow::GetRequiredExtensions(uint32_t* extensionCount) {
	char** glfwExtensions;
	return glfwGetRequiredInstanceExtensions(extensionCount);
}

HWND GLFWWindow::GetWindowHandle() {
	return glfwGetWin32Window(window);
}

void GLFWWindow::InitiWindowSurface(VkInstance* instance, VkSurfaceKHR* windowSurface) {
	if (glfwCreateWindowSurface(*instance, window, nullptr, windowSurface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

void GLFWWindow::GetFrameBufferSize(int* width, int* height) {
	glfwGetFramebufferSize(window, width, height);
}

