#pragma once
#include <unordered_map>
#include <stdexcept>
#include "Backends/BaseBackend.h"
#include "Scene/Components/Cameras/BaseCameraComponent.h"

class RendererModelReference;
class RendererImage2DReference;
class RendererCubemapReference;
class RendererMeshUniformReference;
class RendererPointLightReference;

class Renderer {
	friend class RendererModelReference;
	friend class RendererImage2DReference;
	friend class RendererCubemapReference;
	friend class RendererMeshUniformReference;
	friend class RendererPointLightReference;

public:
	Renderer(BaseBackend& backend);

	const RendererModelReference CreateModel(CPUBaseModel& model);
	const RendererImage2DReference CreateImage2D(CPUImage2D& image);
	const RendererCubemapReference CreateCubemap(CPUCubemap& image);
	const RendererMeshUniformReference CreateMeshUniform(std::string name);
	const RendererPointLightReference CreatePointLight();

	void BeginFrame();
	void UpdateViewMatrix(glm::mat4 view);
	void UpdateProjectionMatrix(glm::mat4 proj);
	void DrawTextured3DMesh(const RendererModelReference modelReference, const RendererImage2DReference imageReference, const RendererMeshUniformReference uniformReference);
	void DrawSkybox(const RendererModelReference modelReference, const RendererCubemapReference imageReference, const RendererMeshUniformReference uniformReference);
	void EndFrame();

private:
	struct FrameData {
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		uint32_t nLights;
	};
	struct PointLightData {
		glm::vec3 position;
	};
	struct MeshUniformData {
		glm::mat4 modelMatrix;
	};

	uint32_t maxPointLights = 64;

	FrameData frameData;
	std::vector<PointLightData> pointLights;
	uint32_t currentLightsNumber = 0;

	BaseBackend& backend;
	BackendPipelineReference meshPipeline;
	BackendPipelineReference skyboxPipeline;
	BackendUniformReference frameUniform;
	BackendStorageBufferReference pointLightsBuffer;
};

class RendererModelReference {
	friend class Renderer;
public:
	RendererModelReference();
	RendererModelReference(Renderer& renderer, BackendModelReference modelReference);

private:
	Renderer* renderer;
	BackendModelReference modelReference;
};

class RendererImage2DReference {
	friend class Renderer;
public:
	RendererImage2DReference();
	RendererImage2DReference(Renderer& renderer, BackendImage2DReference imageReference);

private:
	Renderer* renderer;
	BackendImage2DReference imageReference;
};

class RendererCubemapReference {
	friend class Renderer;
public:
	RendererCubemapReference();
	RendererCubemapReference(Renderer& renderer, BackendCubemapReference cubemapReference);

private:
	Renderer* renderer;
	BackendCubemapReference cubemapReference;
};

class RendererMeshUniformReference {
	friend class Renderer;
public:
	RendererMeshUniformReference();
	RendererMeshUniformReference(Renderer& renderer, BackendUniformReference uniformReference);

	void SetModelMatrix(glm::mat4 model);
	void Update() const;

private:
	Renderer::MeshUniformData meshData;
	Renderer* renderer;
	BackendUniformReference uniformReference;
};

class RendererPointLightReference {
	friend Renderer;
public:
	RendererPointLightReference();
	RendererPointLightReference(Renderer& renderer, Renderer::PointLightData& pointLightData);

	void UpdatePosition(glm::vec3 position);
private:
	Renderer::PointLightData* pointLightData;
	Renderer* renderer;
};