#include "GLFWWindow.h"

void(*GLFWWindow::bufferCallback)(void*) = nullptr;

GLFWWindow::GLFWWindow(const uint32_t w, const uint32_t h, const std::string windowName) :
	BaseWindow(w, h, windowName)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
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
	return glfwGetRequiredInstanceExtensions(extensionCount);
}

void GLFWWindow::InitiWindowSurface(VkInstance* instance, VkSurfaceKHR* windowSurface) {
	if (glfwCreateWindowSurface(*instance, window, nullptr, windowSurface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

void GLFWWindow::GetFrameBufferSize(int* width, int* height) {
	glfwGetFramebufferSize(window, width, height);
}

void GLFWWindow::SetBufferResizeCallback(void* buffer, void(*func)(void*)) {
	glfwSetWindowUserPointer(window, buffer);
	glfwSetFramebufferSizeCallback(window, BufferResizeCallback);
	GLFWWindow::bufferCallback = func;
}


void GLFWWindow::BufferResizeCallback(GLFWwindow* window, int width, int height) {
	void* buffer = glfwGetWindowUserPointer(window);
	bufferCallback(buffer);
}

void GLFWWindow::WaitWhileMinimized() {
	int width = 0, height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}
}
