#pragma once
#include <unordered_map>
#include <stdexcept>
#include "Backends/BaseBackend.h"
#include "Scene/Components/Cameras/BaseCameraComponent.h"

class RendererModelReference;
class RendererImage2DReference;
class RendererCubemapReference;
class RendererMeshUniformReference;
class RendererMaterialUniformReference;
class RendererLightReference;

class Renderer {
	friend class RendererModelReference;
	friend class RendererImage2DReference;
	friend class RendererCubemapReference;
	friend class RendererMeshUniformReference;
	friend class RendererMaterialUniformReference;
	friend class RendererLightReference;

public:
	Renderer(BaseBackend& backend);

	const RendererModelReference CreateModel(CPUBaseModel& model);
	const RendererImage2DReference CreateImage2D(CPUImage2D& image);
	const RendererCubemapReference CreateCubemap(CPUCubemap& image);
	const RendererMeshUniformReference CreateMeshUniform(std::string name);
	const RendererMaterialUniformReference CreateMaterialUniformReference(std::string name);
	const RendererLightReference CreateLight();

	void BeginFrame();
	void UpdateViewMatrix(glm::mat4 view);
	void UpdateProjectionMatrix(glm::mat4 proj);
	void DrawTextured3DMesh(const RendererModelReference modelReference, const RendererImage2DReference imageReference, const RendererMeshUniformReference uniformReference, const RendererMaterialUniformReference materialReference);
	void DrawSkybox(const RendererModelReference modelReference, const RendererCubemapReference imageReference, const RendererMeshUniformReference uniformReference);
	void EndFrame();

private:
	struct FrameData {
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		uint32_t nLights;
	};
	struct LightData {
		glm::vec4 position{ 0, 0, 0, 1};
		glm::vec3 lightColor{ 1, 1, 1 };
		float constantAttenuation{ 1 };
		float linearAttenuation{ 0 };
		float quadraticAttenuation{ 0 };
	};
	struct MeshUniformData {
		glm::mat4 modelMatrix{1};
	};
	struct MaterialUniformData {
		glm::vec3 kAmbient{ 0.1, 0.1, 0.1 };
		glm::vec3 kDiffuse{ 0.1, 0.1, 0.1 };
		glm::vec3 kSpecular{ 0.1, 0.1, 0.1 };
	};

	uint32_t maxLights = 64;

	FrameData frameData;
	std::vector<LightData> lights;
	uint32_t currentLightsNumber = 0;

	BaseBackend& backend;
	BackendPipelineReference meshPipeline;
	BackendPipelineReference skyboxPipeline;
	BackendUniformReference frameUniform;
	BackendStorageBufferReference lightsBuffer;
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

class RendererMaterialUniformReference {
	friend class Renderer;
public:
	RendererMaterialUniformReference();
	RendererMaterialUniformReference(Renderer& renderer, BackendUniformReference uniformReference);

	void SetAmbientCoefficients(glm::vec3 coefficients);
	void SetDiffuseCoefficients(glm::vec3 coefficients);
	void SetSpecularCoefficients(glm::vec3 coefficients);

private:
	Renderer::MaterialUniformData materialData;
	Renderer* renderer;
	BackendUniformReference uniformReference;
};

class RendererLightReference {
	friend Renderer;
public:
	RendererLightReference();
	RendererLightReference(Renderer& renderer, Renderer::LightData& lightData);

	void SetPosition(glm::vec4 position);
	void SetLightColor(glm::vec3 color);
	void SetConstantAttenuation(float attenuation);
	void SetLinearAttenuation(float attenuation);
	void SetQuadraticAttenuation(float attenuation);
private:
	Renderer::LightData* lightData;
	Renderer* renderer;
};