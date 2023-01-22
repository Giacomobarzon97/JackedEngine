#pragma once

#include <string>
#include "Windows\BaseWindow.h"
#include "Rendering/Renderer.h"

class JackedEngine {
public:
	JackedEngine();
	JackedEngine(JackedEngine &) = delete;
	~JackedEngine();
	JackedEngine &operator=(JackedEngine &) = delete;

private:
	static const std::string APP_NAME;
	static const uint32_t  WINDOW_WIDTH;
	static const uint32_t  WINDOW_HEIGHT;

	BaseWindow* window;
	Renderer* renderer;

	void mainLoop();
};
