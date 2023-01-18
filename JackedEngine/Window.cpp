#include "Window.h"

Window::Window(const uint32_t w, const uint32_t h, const std::string windowName) : 
	width( w ), 
	height( h ), 
	windowName( windowName ) 
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

Window::~Window() {
	if (vkInstance.has_value()) {
		vkDestroySurfaceKHR(*vkInstance.value(), surface, nullptr);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::ShouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::PollEvents() {
	glfwPollEvents();
}

void Window::InitSurface(VkInstance* vkInstance) {
	this->vkInstance = vkInstance;

	VkWin32SurfaceCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.hwnd = glfwGetWin32Window(window);
	createInfo.hinstance = GetModuleHandle(nullptr);
	if (vkCreateWin32SurfaceKHR(*vkInstance, &createInfo, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
	if (glfwCreateWindowSurface(*vkInstance, window, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}

}

const char** Window::GetRequiredExtensions(uint32_t* extensionCount) {
	char** glfwExtensions;
	return glfwGetRequiredInstanceExtensions(extensionCount);
}
