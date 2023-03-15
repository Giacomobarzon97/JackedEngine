#pragma once

#include <string>
#include "Scene\SceneObjects\Cameras\BaseCameraObject.h"
#include "Windows\BaseWindow.h"
#include "Rendering\Renderer.h"

class JackedEngine {
public:
	JackedEngine();
	JackedEngine(JackedEngine &) = delete;
	~JackedEngine();
	JackedEngine &operator=(JackedEngine &) = delete;

private:
	static const std::string APP_NAME;
	static const uint32_t  WINDOW_WIDTH = 800;
	static const uint32_t  WINDOW_HEIGHT = 600;
	const int MAX_FRAMES_IN_FLIGHT = 2;

	BaseCameraObject* camera;
	BaseWindow* window;
	Renderer* renderer;

	void mainLoop();
};
