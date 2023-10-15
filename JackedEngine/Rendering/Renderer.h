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
	void UpdateViewMatrix(glm::mat4 view);
	void UpdateProjectionMatrix(glm::mat4 proj);
	void UpdateMeshUniformData(const BackendUniformReference uniformReference, const MeshUniformData& meshUniformData);
	void DrawMesh(const BackendModelReference modelReference, const BackendImage2DReference imageReference, const BackendUniformReference uniformReference);
	void DrawSkybox(const BackendModelReference modelReference, const BackendCubemapReference imageReference, const BackendUniformReference uniformReference);
	void EndFrame();

private:
	struct FrameData {
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};

	uint32_t maxPointLights = 64;
	FrameData frameData;
		 
	BaseBackend& backend;
	BackendPipelineReference meshPipeline;
	BackendPipelineReference skyboxPipeline;
	BackendUniformReference frameUniform;
	BackendStorageBufferReference pointLightsBuffer;
};