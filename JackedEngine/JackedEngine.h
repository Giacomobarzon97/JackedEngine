#pragma once

#include <string>
#include "Window.h"
#include "Rendering/Renderer.h"

class JackedEngine {
public:
	JackedEngine();

	JackedEngine(const JackedEngine &) = delete;
	JackedEngine &operator=(const JackedEngine &) = delete;

private:
	static const std::string APP_NAME;
	static const uint32_t  WINDOW_WIDTH;
	static const uint32_t  WINDOW_HEIGHT;

	Window window;
	Renderer renderer;
	void mainLoop();
};
