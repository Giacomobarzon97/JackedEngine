#include "JackedEngine.h"

const std::string JackedEngine::APP_NAME = "JackedEngine";
const uint32_t  JackedEngine::WINDOW_WIDTH =  800;
const uint32_t  JackedEngine::WINDOW_HEIGHT = 800;

JackedEngine::JackedEngine()
{
	window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = Window::GetRequiredExtensions(&glfwExtensionCount);

	renderer = new Renderer(APP_NAME, glfwExtensions, glfwExtensionCount, window->getGLFWWindow());

	mainLoop();
}

JackedEngine::~JackedEngine() {
	delete window;
}


void JackedEngine::mainLoop() {
	while (!window->ShouldClose()) {
		window->PollEvents();
	}
}