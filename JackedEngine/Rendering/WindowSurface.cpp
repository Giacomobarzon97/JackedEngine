#include "WindowSurface.h"

WindowSurface::WindowSurface(Instance* instance, BaseWindow* window) :
	instance(instance)
{
	VkWin32SurfaceCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.hwnd = window->GetWindowHandle();
	createInfo.hinstance = GetModuleHandle(nullptr);
	if (vkCreateWin32SurfaceKHR(*instance->GetVkInstance(), &createInfo, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

WindowSurface::~WindowSurface() {
	vkDestroySurfaceKHR(*instance->GetVkInstance(), surface, nullptr);
}

VkSurfaceKHR* WindowSurface::getVkSurface() {
	return &surface;
}