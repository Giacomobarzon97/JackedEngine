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

void JackedEngine::MainLoop() {
	FrameData frameData;
	std::chrono::steady_clock::time_point prevFrameTime = std::chrono::high_resolution_clock::now();

	while (!window->ShouldClose()) {
		double deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(std::chrono::high_resolution_clock::now() - prevFrameTime).count();
		ComponentsIterator componentsIterator = world.GetComponentIterator();
		renderer.BeginFrame();

		if (camera.has_value()) {
			int width, height;
			window.get()->GetFrameBufferSize(&width, &height);

			if (width > 0 && height > 0) {
				camera.value()->UpdateCameraStatus();
				frameData.viewMatrix = camera.value()->GetViewMatrix();
				frameData.projectionMatrix = camera.value()->GetProjectionMatrix(width, height);
				renderer.UpdateFrameData(frameData);

				while (componentsIterator.HasNext()) {
					SceneComponent* currentComponent = componentsIterator.Next();
					currentComponent->Tick(deltaTime);
				}
			}
		}

		renderer.EndFrame();

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

void JackedEngine::SetActiveCamera(BaseCameraComponent& camera) {
	JackedEngine::camera = &camera;
}