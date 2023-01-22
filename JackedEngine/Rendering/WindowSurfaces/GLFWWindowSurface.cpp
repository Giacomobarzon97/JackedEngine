#include "GLFWWindowSurface.h"

GLFWWindowSurface::GLFWWindowSurface(Instance* instance, GLFWwindow* window) {
	this->window = window;
	BaseWindowSurface::instance = instance;

	VkWin32SurfaceCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.hwnd = glfwGetWin32Window(window);
	createInfo.hinstance = GetModuleHandle(nullptr);
	if (vkCreateWin32SurfaceKHR(instance->GetVkInstance(), &createInfo, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
	if (glfwCreateWindowSurface(instance->GetVkInstance(), window, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

GLFWWindowSurface::~GLFWWindowSurface(){
	vkDestroySurfaceKHR(instance->GetVkInstance(), surface, nullptr);
}