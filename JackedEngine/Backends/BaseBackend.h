#pragma once
#include "Backends/CPUResources/CPUModels/CPUBaseModel.h"
#include "Backends/CPUResources/CPUImages/CPUImage2D.h"
#include "Backends/CPUResources/CPUImages/CPUCubemap.h"
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
	STORAGE_BUFFER,
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

	virtual const BackendPipelineReference CreatePipeline(PipelineCreateInfo createInfo) = 0;
	virtual const BackendModelReference CreateModel(CPUBaseModel& model) = 0;
	virtual const BackendImage2DReference CreateImage2D(CPUImage2D& image) = 0;
	virtual const BackendCubemapReference CreateCubemap(CPUCubemap& image) = 0;
	virtual const BackendUniformReference CreateUniform(const std::string uniformId, const uint32_t uniformSize) = 0;
	virtual const BackendStorageBufferReference CreateStorageBuffer(const std::string storageId, const uint32_t elementSize, const uint32_t maxElements) = 0;

	virtual void UpdateUniform(const BackendUniformReference uniform, const void* uniformData) = 0;
	virtual void UpdateStorageBuffer(const BackendStorageBufferReference storage, const void* storageData, const uint32_t nElements) = 0;

	virtual void BindPipeline(const BackendPipelineReference shader) = 0;
	virtual void BindModel(const BackendModelReference model) = 0;
	virtual void BindImage2D(const uint32_t location, const BackendImage2DReference image) = 0;
	virtual void BindCubemap(const uint32_t location, const BackendCubemapReference image) = 0;
	virtual void BindUniform(const uint32_t location, const BackendUniformReference uniform) = 0;
	virtual void BindStorageBuffer(const uint32_t location, const BackendStorageBufferReference storage) = 0;

	virtual void BeginFrame() = 0;
	virtual void Draw() = 0;
	virtual void EndFrame() = 0;
};