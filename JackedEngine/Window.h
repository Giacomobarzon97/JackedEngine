#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window(const uint32_t w, const uint32_t h, const std::string windowName);
	~Window();

	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;

	bool ShouldClose();
	void PollEvents();
	static const char** GetRequiredExtensions(uint32_t* extensionCount);

private: 
	const uint32_t width;
	const uint32_t height;
	const std::string windowName;
	GLFWwindow *window;
};

