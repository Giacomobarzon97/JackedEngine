#pragma once
#include <memory>
#include <optional>
#include "Scene/Components/Cameras/BaseCameraComponent.h"
#include "Scene/World.h"
#include "Windows/BaseWindow.h"
#include "Backends/BaseBackend.h"
#include "Rendering/Renderer.h"
#include "Input/InputManager.h"

class JackedEngine {
public:
	JackedEngine() = delete;
	JackedEngine(JackedEngine &) = delete;
	~JackedEngine() = delete;
	JackedEngine &operator=(JackedEngine &) = delete;

	static void MainLoop();

	static Renderer& GetRenderer();
	static InputManager& GetInputManager();
	static World& GetWorld();
	static void SetActiveCamera(BaseCameraComponent& camera);

private:
	static const std::string APP_NAME;
	static const uint32_t  WINDOW_WIDTH = 1920;
	static const uint32_t  WINDOW_HEIGHT = 1080;
	const int MAX_FRAMES_IN_FLIGHT = 2;

	static World world;
	static std::optional<BaseCameraComponent*> camera;
	static std::unique_ptr <BaseWindow> window;
	static std::unique_ptr <BaseBackend> backend;
	static Renderer renderer;
	static InputManager inputManager;
};
