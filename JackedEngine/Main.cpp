#include "Window.h"
#include "Pipeline.h"

int main() {
	Window window{ 800, 800, "Hello Vulkan!" };
	Pipeline pipeline{"Shaders/default.vert.spv", "Shaders/default.frag.spv"};

	while (!window.shouldClose()) {
		glfwPollEvents();
	}
}
