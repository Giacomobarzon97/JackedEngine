#include "JackedEngine.h"
#include "Windows/GLFWWindow.h"

const std::string JackedEngine::APP_NAME = "JackedEngine";
const uint32_t  JackedEngine::WINDOW_WIDTH =  800;
const uint32_t  JackedEngine::WINDOW_HEIGHT = 800;

JackedEngine::JackedEngine()
{
	window = new GLFWWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);

	renderer = new Renderer(window);

	mainLoop();
}

JackedEngine::~JackedEngine() {
	delete renderer;
	delete window;
}


void JackedEngine::mainLoop() {
	while (!window->ShouldClose()) {
		window->PollEvents();
	}
}