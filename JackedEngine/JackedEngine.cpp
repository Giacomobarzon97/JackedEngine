#include "JackedEngine.h"
#include "Scene/Components/Cameras/PerspectiveCamera.h"
#include "Backends/Vulkan/VulkanBackend.h"
#include "Windows/GLFWWindow.h"
#include <chrono>

const std::string JackedEngine::APP_NAME = "JackedEngine";
std::unique_ptr<BaseCameraComponent> JackedEngine::camera = std::unique_ptr<PerspectiveCamera>(new PerspectiveCamera("Camera", { 2,2,2 }, { -2,-2,-2 }));
std::unique_ptr<BaseWindow> JackedEngine::window = std::unique_ptr<GLFWWindow>(new GLFWWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME));
std::unique_ptr<BaseBackend> JackedEngine::renderer = std::unique_ptr<BaseBackend>(new VulkanBackend(*window, *camera));

void JackedEngine::MainLoop(std::vector<RenderableComponent*> objects) {

	std::chrono::steady_clock::time_point prevFrameTime = std::chrono::high_resolution_clock::now();
	while (!window->ShouldClose()) {
		renderer->BeginFrame();
		std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		float delta = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - prevFrameTime).count();
		prevFrameTime = currentTime;
		for (unsigned int i = 0; i < objects.size(); i++) {
			window->PollEvents();
			objects[i]->Draw();
		}
		renderer->EndFrame();
	}

	renderer->Reset();
	
}

BaseBackend& JackedEngine::Renderer() {
	return *renderer;
}