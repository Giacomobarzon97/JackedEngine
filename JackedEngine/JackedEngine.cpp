#include "JackedEngine.h"
#include "Windows/GLFWWindow.h"

const std::string JackedEngine::APP_NAME = "JackedEngine";

JackedEngine::JackedEngine()
{
	window = new GLFWWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);

	renderer = new Renderer(window, MAX_FRAMES_IN_FLIGHT);

	mainLoop();
}

JackedEngine::~JackedEngine() {
	delete renderer;
	delete window;
}


void JackedEngine::mainLoop() {
	while (!window->ShouldClose()) {
		window->PollEvents();
		renderer->drawFrame();
	}
	renderer->reset();
}