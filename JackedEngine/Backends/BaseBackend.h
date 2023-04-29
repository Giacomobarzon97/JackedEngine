#pragma once
#include "Backends/CPUResources/CPUModels/CPUBaseModel.h"
#include "Backends/CPUResources/CPUImage.h"
#include "Scene/Components/Cameras/BaseCameraComponent.h"

struct TextureReference {
	std::string id;
};

struct ModelReference {
	std::string id;
};

enum ShaderType {
	OBJECT3D,
	SKYBOX
};

class BaseBackend {
public:
	virtual ~BaseBackend();

	virtual TextureReference CreateTexture(CPUImage& image) = 0;
	virtual ModelReference CreateModel(CPUBaseModel& model) = 0;

	virtual void BeginFrame(const BaseCameraComponent& camera) = 0;
	virtual void Draw(const ShaderType shaderType, const ModelReference modelReference, const TextureReference textureReference, const void* constData) = 0;
	virtual void NextRenderPass() = 0;
	virtual void EndFrame() = 0;
	virtual void Reset() = 0;


};