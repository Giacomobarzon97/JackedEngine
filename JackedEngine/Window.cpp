#include "Window.h"



Window::Window(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}
