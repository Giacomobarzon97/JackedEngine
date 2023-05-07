#pragma once
#include "Backends/BaseBackend.h"
#include "Scene/Components/Cameras/BaseCameraComponent.h"

class Renderer {
public:
	Renderer(BaseBackend& backend);

	const ModelReference CreateModel(CPUBaseModel& model);
	const ImageReference CreateImage(CPUImage& image);

	void BeginFrame();
	void UpdateCamera(const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix);
	void Draw(const ModelReference modelReference, const ImageReference imageReference, const glm::mat4 modelMatrix, const ShaderType shaderType);
	void EndFrame();

private:
	struct FrameData {
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};

	struct ModelData {
		glm::mat4 modelMatrix;
	};

	BaseBackend& backend;

	UniformReference frameUniform;
	UniformReference modelUniform;
};