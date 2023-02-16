#include "JackedEngine.h"
#include "Windows/GLFWWindow.h"

const std::string JackedEngine::APP_NAME = "JackedEngine";

JackedEngine::JackedEngine()
{
	window = new GLFWWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);

	camera = new CameraObject(*window);

	renderer = new Renderer(*window, *camera);

	mainLoop();
}

JackedEngine::~JackedEngine() {
	delete renderer;
	delete window;
}


void JackedEngine::mainLoop() {
	static auto startTime = std::chrono::high_resolution_clock::now();


	while (!window->ShouldClose()) {
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
		//camera->Translate(time / 100,0, 0);
		window->PollEvents();
		renderer->DrawFrame();
	}
	renderer->Reset();
}