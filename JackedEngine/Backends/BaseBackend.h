#pragma once
#include "Backends/CPUResources/CPUModels/CPUBaseModel.h"
#include "Backends/CPUResources/CPUImage.h"
#include "Scene/Components/Cameras/BaseCameraComponent.h"
#include "Backends/BackendTypes.h"

class BaseBackend {
public:
	virtual ~BaseBackend();

	virtual const ModelReference CreateModel(CPUBaseModel& model) = 0;
	virtual const ImageReference CreateImage(CPUImage& image) = 0;
	virtual const UniformReference CreateUniform(const std::string uniformId, const uint32_t uniformSize) = 0;

	virtual void UpdateUniform(const UniformReference uniform, const void* uniformData) = 0;

	virtual void BindPipeline(const ShaderType shaderType) = 0;
	virtual void BindModel(const ModelReference model) = 0;
	virtual void BindImage(const uint32_t location, const ImageReference texture) = 0;
	virtual void BindUniform(const uint32_t location, const UniformReference uniform) = 0;

	virtual void BeginFrame() = 0;
	virtual void Draw() = 0;
	virtual void EndFrame() = 0;
	virtual void Reset() = 0;


};