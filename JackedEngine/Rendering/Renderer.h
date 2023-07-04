#pragma once
#include <unordered_map>
#include "Backends/BaseBackend.h"
#include "Scene/Components/Cameras/BaseCameraComponent.h"
#include "Rendering/RenderTypes.h"

class Renderer {
public:
	Renderer(BaseBackend& backend);

	const ModelReference CreateModel(CPUBaseModel& model);
	const ImageReference CreateImage(CPUImage& image);
	const UniformReference CreateComponentUniform(std::string name);

	void BeginFrame();
	void UpdateCamera(const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix);
	void UpdateComponentData(const UniformReference uniformReference, const ComponentData componentData);
	void Draw(const ModelReference modelReference, const ImageReference imageReference, const UniformReference uniformReference, const ShaderType shaderType);
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

	std::unordered_map<ShaderType, PipelineReference> pipelineMap;

	UniformReference frameUniform;
};