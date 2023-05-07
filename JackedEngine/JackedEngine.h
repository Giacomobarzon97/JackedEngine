#pragma once
#include <memory>
#include <optional>
#include "Scene\Components\Cameras\BaseCameraComponent.h"
#include "Scene\Components\RenderableComponent.h"
#include "Scene\World.h"
#include "Windows\BaseWindow.h"
#include "Backends\BaseBackend.h"

class JackedEngine {
public:
	JackedEngine() = delete;
	JackedEngine(JackedEngine &) = delete;
	~JackedEngine() = delete;
	JackedEngine &operator=(JackedEngine &) = delete;

	static void MainLoop();

	static BaseBackend& GetRenderer();
	static World& GetWorld();
	static void SetActiveCamera(BaseCameraComponent& camera);

private:
	struct FrameData {
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};

	struct ModelData {
		glm::mat4 modelMatrix;
	};

	static const std::string APP_NAME;
	static const uint32_t  WINDOW_WIDTH = 800;
	static const uint32_t  WINDOW_HEIGHT = 600;
	const int MAX_FRAMES_IN_FLIGHT = 2;

	static World world;
	static std::optional<BaseCameraComponent*> camera;
	static std::unique_ptr <BaseWindow> window;
	static std::unique_ptr <BaseBackend> renderer;
};
