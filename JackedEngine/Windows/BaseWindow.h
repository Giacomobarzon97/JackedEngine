#pragma once

#include <string>
#include <Windows.h>

class BaseWindow {

public:
	BaseWindow(uint32_t width, uint32_t height, std::string windowName);
	BaseWindow(BaseWindow &) = delete;
	BaseWindow &operator=(BaseWindow &) = delete;

	const std::string GetWindowName() const;

	virtual ~BaseWindow() = 0;
	virtual const bool ShouldClose() const = 0;
	virtual void PollEvents() const = 0;
	virtual const char** GetRequiredExtensions(uint32_t& extensionCount) const = 0;
	virtual const HWND GetWindowHandle() const = 0;
	virtual void GetFrameBufferSize(int* width, int* height) const = 0;
	virtual void SetBufferResizeCallback(void* buffer, void (*func)(void*)) const = 0;
	virtual void WaitWhileMinimized() const = 0;

protected:
	const uint32_t width;
	const uint32_t height;
	const std::string windowName;
};