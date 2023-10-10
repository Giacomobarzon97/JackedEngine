#pragma once
#include <unordered_map>
#include "Backends/BaseBackend.h"
#include "Scene/Components/Cameras/BaseCameraComponent.h"
#include "Rendering/RenderTypes.h"

class Renderer {
public:
	Renderer(BaseBackend& backend);

	const BackendModelReference CreateModel(CPUBaseModel& model);
	const BackendImage2DReference CreateImage2D(CPUImage2D& image);
	const BackendCubemapReference CreateCubemap(CPUCubemap& image);
	const BackendUniformReference CreateMeshUniform(std::string name);

	void BeginFrame();
	void UpdateFrameData(const FrameData& frameData);
	void UpdateMeshUniformData(const BackendUniformReference uniformReference, const MeshUniformData& meshUniformData);
	void Draw(const BackendModelReference modelReference, const BackendImage2DReference imageReference, const BackendUniformReference uniformReference, const ShaderType shaderType);
	void Draw(const BackendModelReference modelReference, const BackendCubemapReference imageReference, const BackendUniformReference uniformReference, const ShaderType shaderType);
	void EndFrame();

private:
	BaseBackend& backend;
	std::unordered_map<ShaderType, BackendPipelineReference> pipelineMap;

	BackendUniformReference frameUniform;
};