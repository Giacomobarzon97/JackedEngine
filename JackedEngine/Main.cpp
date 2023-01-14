#include "Window.h"

int main() {
	Window window{ 800, 800, "Hello Vulkan!" };
	while (!window.shouldClose()) {
		glfwPollEvents();
	}
}
