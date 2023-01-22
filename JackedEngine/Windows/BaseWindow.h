#pragma once

#include <string>
#include <Windows.h>
#include "Rendering/Instance.h"

class BaseWindow {

public:
	BaseWindow(uint32_t width, uint32_t height, std::string windowName);
	virtual bool ShouldClose() = 0;
	virtual void PollEvents() = 0;
	virtual const char** GetRequiredExtensions(uint32_t* extensionCount) = 0;
	virtual HWND GetWindowHandle() = 0;
	virtual void InitiWindowSurface(Instance* instance, VkSurfaceKHR* windowSurface) = 0;

protected:
	const uint32_t width;
	const uint32_t height;
	const std::string windowName;
};