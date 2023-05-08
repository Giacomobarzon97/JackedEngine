#pragma once
#include "Backends/CPUResources/CPUModels/CPUBaseModel.h"
#include "Backends/CPUResources/CPUImage.h"
#include "Scene/Components/Cameras/BaseCameraComponent.h"
#include "Backends/BackendTypes.h"

enum VertexType {
	VERTEX_TYPE_UNDEFINED,
	FLOAT_32,
	INT_32
};

enum AttachmentType {
	ATTACHMENT_TYPE_UNDEFINED,
	IMAGE,
	UNIFORM,
};

struct VertexInfo {
	uint8_t size;
	VertexType type;
};

struct PipelineCreateInfo {
	std::string id;
	std::string vertexShader;
	std::string fragmentShader;
	std::vector<AttachmentType> attachments;
	std::vector<VertexInfo> vertices;
};

class BaseBackend {
public:
	virtual ~BaseBackend();

	virtual const PipelineReference CreatePipeline(PipelineCreateInfo createInfo) = 0;
	virtual const ModelReference CreateModel(CPUBaseModel& model) = 0;
	virtual const ImageReference CreateImage(CPUImage& image) = 0;
	virtual const UniformReference CreateUniform(const std::string uniformId, const uint32_t uniformSize) = 0;

	virtual void UpdateUniform(const UniformReference uniform, const void* uniformData) = 0;

	virtual void BindPipeline(const PipelineReference shader) = 0;
	virtual void BindModel(const ModelReference model) = 0;
	virtual void BindImage(const uint32_t location, const ImageReference image) = 0;
	virtual void BindUniform(const uint32_t location, const UniformReference uniform) = 0;

	virtual void BeginFrame() = 0;
	virtual void Draw() = 0;
	virtual void EndFrame() = 0;
};