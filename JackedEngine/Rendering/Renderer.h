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
	const UniformReference CreateMeshUniform(std::string name);

	void BeginFrame();
	void UpdateFrameData(const FrameData& frameData);
	void UpdateMeshUniformData(const UniformReference uniformReference, const MeshUniformData& meshUniformData);
	void Draw(const ModelReference modelReference, const ImageReference imageReference, const UniformReference uniformReference, const ShaderType shaderType);
	void EndFrame();

private:
	BaseBackend& backend;

	std::unordered_map<ShaderType, PipelineReference> pipelineMap;

	UniformReference frameUniform;
};