#include "GLFWWindowSurface.h"

GLFWWindowSurface::GLFWWindowSurface(VkInstance* vkInstance, GLFWwindow* window)
{
	BaseWindowSurface::vkInstance = vkInstance;
	this->window = window;

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
GLFWWindowSurface::~GLFWWindowSurface(){
	vkDestroySurfaceKHR(*vkInstance, surface, nullptr);
}