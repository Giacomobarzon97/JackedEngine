#pragma once
#include <unordered_map>
#include "Backends/BaseBackend.h"
#include "Scene/Components/Cameras/BaseCameraComponent.h"
#include "Rendering/RenderTypes.h"

class Renderer {
public:
	Renderer(BaseBackend& backend);

	const BackendModelReference CreateModel(CPUBaseModel& model);
	const BackendImageReference CreateImage(CPUImage& image);
	const BackendUniformReference CreateMeshUniform(std::string name);

	void BeginFrame();
	void UpdateFrameData(const FrameData& frameData);
	void UpdateMeshUniformData(const BackendUniformReference uniformReference, const MeshUniformData& meshUniformData);
	void Draw(const BackendModelReference modelReference, const BackendImageReference imageReference, const BackendUniformReference uniformReference, const ShaderType shaderType);
	void EndFrame();

private:
	BaseBackend& backend;
	std::unordered_map<ShaderType, BackendPipelineReference> pipelineMap;

	BackendUniformReference frameUniform;
};