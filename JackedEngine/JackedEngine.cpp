#include "JackedEngine.h"
#include "Backends/Vulkan/VulkanBackend.h"
#include "Windows/GLFWWindow.h"
#include <chrono>

const std::string JackedEngine::APP_NAME = "JackedEngine";

World JackedEngine::world;
std::optional<BaseCameraComponent*> JackedEngine::camera;
std::unique_ptr<BaseWindow> JackedEngine::window = std::unique_ptr<GLFWWindow>(new GLFWWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME));
std::unique_ptr<BaseBackend> JackedEngine::backend = std::unique_ptr<BaseBackend>(new VulkanBackend(*window));
Renderer JackedEngine::renderer = Renderer(*backend);
InputManager JackedEngine::inputManager(*window);

void JackedEngine::MainLoop() {
	std::chrono::steady_clock::time_point prevFrameTime = std::chrono::high_resolution_clock::now();

	while (!window->ShouldClose()) {
		double deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(std::chrono::high_resolution_clock::now() - prevFrameTime).count();
		std::vector<BaseActor*> actors = world.GetActors();

		if (camera.has_value()) {
			int width, height;
			window.get()->GetFrameBufferSize(&width, &height);
			if (width > 0 && height > 0) {
				renderer.BeginFrame();
				for (BaseActor* actor : actors) {
					actor->Tick(deltaTime);
				}
				renderer.UpdateViewMatrix(camera.value()->GetViewMatrix());
				renderer.UpdateProjectionMatrix(camera.value()->GetProjectionMatrix(width, height));
				renderer.EndFrame();
			}
		}

		window->PollEvents();
		prevFrameTime = std::chrono::high_resolution_clock::now();
	}
}

Renderer& JackedEngine::GetRenderer() {
	return renderer;
}

World& JackedEngine::GetWorld() {
	return world;
}

InputManager& JackedEngine::GetInputManager() {
	return inputManager;
}

void JackedEngine::SetActiveCamera(BaseCameraComponent& camera) {
	JackedEngine::camera = &camera;
}