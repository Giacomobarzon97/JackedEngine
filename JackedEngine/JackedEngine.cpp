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

	UniformReference frameUniform = renderer->CreateUniform("FrameData", sizeof(FrameData));
	UniformReference modelUniform = renderer->CreateUniform("ModelData", sizeof(ModelData));


	std::vector<SceneComponent*> components = world.GetComponents();
	for (unsigned int i = 0; i < components.size(); i++) {
		components[i]->Init();
	}

	std::chrono::steady_clock::time_point prevFrameTime = std::chrono::high_resolution_clock::now();

	while (!window->ShouldClose()) {
		renderer->BeginFrame();

		if (camera.has_value()) {
			components = world.GetComponents();
			int width, height;
			window.get()->GetFrameBufferSize(&width, &height);

			if (width > 0 && height > 0) {
				FrameData frameData{};
				frameData.projectionMatrix = camera.value()->GetProjectionMatrix(width, height);
				frameData.viewMatrix = camera.value()->GetViewMatrix();
				renderer->UpdateUniform(frameUniform, &frameData);

				for (unsigned int i = 0; i < components.size(); i++) {
					const RenderableComponent* renderableComponent = dynamic_cast<const RenderableComponent*>(components[i]);
					if (renderableComponent != nullptr) {
						ModelData modelData{};
						modelData.modelMatrix = renderableComponent->GetModelMatrix();
						renderer->UpdateUniform(modelUniform, &modelData);

						renderer->BindPipeline(renderableComponent->GetShaderType());
						renderer->BindModel(renderableComponent->GetModel());
						renderer->BindUniform(0, frameUniform);
						renderer->BindUniform(1, modelUniform);
						renderer->BindImage(2, renderableComponent->GetMaterial().GetDiffuseTexture());
						renderer->Draw();
					}
				}
			}
		}

		renderer->EndFrame();

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