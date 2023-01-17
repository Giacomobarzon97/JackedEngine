#include "JackedEngine.h"

const std::string JackedEngine::APP_NAME = "JackedEngine";
const uint32_t  JackedEngine::WINDOW_WIDTH =  800;
const uint32_t  JackedEngine::WINDOW_HEIGHT = 800;

JackedEngine::JackedEngine() :
	window(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME)
{
	mainLoop();
}

void JackedEngine::mainLoop() {
	while (!window.ShouldClose()) {
		window.PollEvents();
	}
}