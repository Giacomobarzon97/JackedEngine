#include "JackedEngine.h"

const std::string JackedEngine::APP_NAME = "JackedEngine";
const uint32_t  JackedEngine::WINDOW_WIDTH =  800;
const uint32_t  JackedEngine::WINDOW_HEIGHT = 800;

JackedEngine::JackedEngine() :
	window(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME)
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = Window::GetRequiredExtensions(&glfwExtensionCount);
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	renderer = new Renderer(APP_NAME, extensions);

	mainLoop();
}

JackedEngine::~JackedEngine() {
	delete renderer;
}


void JackedEngine::mainLoop() {
	while (!window.ShouldClose()) {
		window.PollEvents();
	}
}