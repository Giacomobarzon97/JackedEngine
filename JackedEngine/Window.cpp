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
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::ShouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::PollEvents() {
	glfwPollEvents();
}

const char** Window::GetRequiredExtensions(uint32_t* extensionCount) {
	char** glfwExtensions;
	return glfwGetRequiredInstanceExtensions(extensionCount);
}

GLFWwindow* Window::getGLFWWindow() {
	return window;
}
