#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <string>
#include <stdexcept>
#include "BaseWindow.h"

class GLFWWindow : public BaseWindow
{
public:
	GLFWWindow(const uint32_t w, const uint32_t h, const std::string windowName);
	GLFWWindow(GLFWWindow &) = delete;
	virtual ~GLFWWindow() override;
	GLFWWindow &operator=(GLFWWindow &) = delete;

	virtual const HWND GetWindowHandle() const override;
	virtual const bool ShouldClose() const override;
	virtual void PollEvents() const override;
	virtual const char** GetRequiredExtensions(uint32_t& extensionCount) const override;
	virtual void GetFrameBufferSize(int* width, int* height) const override;
	virtual void SetBufferResizeCallback(void* buffer, void(*func)(void*)) override;
	virtual void WaitWhileMinimized() const override;

private:
	const static std::unordered_map<int, InputKey> keyMap;
	const static std::unordered_map<int, InputEvent> eventMap;

	void* buffer = nullptr;
	GLFWwindow *window;
	static void (*bufferCallback)(void*);

	static void BufferResizeCallback(GLFWwindow* window, int width, int height);
	static void KeyPresseedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

