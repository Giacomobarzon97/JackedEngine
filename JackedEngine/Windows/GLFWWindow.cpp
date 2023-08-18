#include "GLFWWindow.h"
#include <iostream>

const std::unordered_map<int, BindableKey> GLFWWindow::keyMap = {
	{GLFW_KEY_W, KEY_W},
	{GLFW_KEY_A, KEY_A},
	{GLFW_KEY_S, KEY_S},
	{GLFW_KEY_D, KEY_D}
};

void(*GLFWWindow::bufferCallback)(void*) = nullptr;

GLFWWindow::GLFWWindow(const uint32_t w, const uint32_t h, const std::string windowName) :
	BaseWindow(w, h, windowName)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, BufferResizeCallback);
	glfwSetKeyCallback(window, KeyPresseedCallback);
}

GLFWWindow::~GLFWWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

const bool GLFWWindow::ShouldClose() const {
	return glfwWindowShouldClose(window);
}

void GLFWWindow::PollEvents() const {
	glfwPollEvents();
}

const char** GLFWWindow::GetRequiredExtensions(uint32_t& extensionCount) const {
	return glfwGetRequiredInstanceExtensions(&extensionCount);
}

const HWND GLFWWindow::GetWindowHandle() const {
	return glfwGetWin32Window(window);
}


void GLFWWindow::GetFrameBufferSize(int* width, int* height) const {
	glfwGetFramebufferSize(window, width, height);
}

void GLFWWindow::SetBufferResizeCallback(void* buffer, void(*func)(void*)) {
	this->buffer = buffer;
	GLFWWindow::bufferCallback = func;
}

void GLFWWindow::BufferResizeCallback(GLFWwindow* window, int width, int height) {
	void* buffer = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->buffer;
	bufferCallback(buffer);
}

void GLFWWindow::WaitWhileMinimized() const {
	int width = 0, height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}
}

void GLFWWindow::KeyPresseedCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	auto bindings = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->functionBindings;
	auto pressedKey = keyMap.find(key);
	if (pressedKey != keyMap.end()) {
		auto functionList = bindings.find(pressedKey->second);
		if (functionList != bindings.end()) {
			for (auto binding : functionList->second) {
				binding();
			}
		}
	}
}