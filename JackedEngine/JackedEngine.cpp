#include "JackedEngine.h"
#include "Backends/Vulkan/VulkanBackend.h"
#include "Windows/GLFWWindow.h"
#include <chrono>

const std::string JackedEngine::APP_NAME = "JackedEngine";
std::unique_ptr<BaseWindow> JackedEngine::window = std::unique_ptr<GLFWWindow>(new GLFWWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME));
std::unique_ptr<BaseBackend> JackedEngine::renderer = std::unique_ptr<BaseBackend>(new VulkanBackend(*window));
std::optional<BaseCameraComponent*> JackedEngine::camera;
World JackedEngine::world;

void JackedEngine::MainLoop() {

	std::vector<SceneComponent*> components = world.GetComponents();
	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->Init();
	}

	std::chrono::steady_clock::time_point prevFrameTime = std::chrono::high_resolution_clock::now();

	while (!window->ShouldClose()) {
		if (camera.has_value()) {
			components = world.GetComponents();
			renderer->BeginFrame(*camera.value());
			for (unsigned int i = 0; i < components.size(); i++) {
				const RenderableComponent* renderableComponent = dynamic_cast<const RenderableComponent*>(components[i]);
				if (renderableComponent != nullptr) {
					renderableComponent->Draw();
				}
			}
			renderer->EndFrame();
		}

		window->PollEvents();

		std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		float delta = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - prevFrameTime).count();
		prevFrameTime = currentTime;
	}

	renderer->Reset();
}

BaseBackend& JackedEngine::GetRenderer() {
	return *renderer;
}

World& JackedEngine::GetWorld() {
	return world;
}

void JackedEngine::SetActiveCamera(BaseCameraComponent& camera) {
	JackedEngine::camera = &camera;
}