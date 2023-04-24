#pragma once

#include <string>
#include <memory>
#include "Scene\Components\Cameras\BaseCameraComponent.h"
#include "Scene\Components\RenderableComponent.h"
#include "Windows\BaseWindow.h"
#include "Backends\BaseBackend.h"

class JackedEngine {
public:
	JackedEngine() = delete;
	JackedEngine(JackedEngine &) = delete;
	~JackedEngine() = delete;
	JackedEngine &operator=(JackedEngine &) = delete;

	static void MainLoop(std::vector<RenderableComponent*> objects);

	static BaseBackend& Renderer();

private:
	static const std::string APP_NAME;
	static const uint32_t  WINDOW_WIDTH = 800;
	static const uint32_t  WINDOW_HEIGHT = 600;
	const int MAX_FRAMES_IN_FLIGHT = 2;

	static std::unique_ptr<BaseCameraComponent> camera;
	static std::unique_ptr <BaseWindow> window;
	static std::unique_ptr <BaseBackend> renderer;
};
