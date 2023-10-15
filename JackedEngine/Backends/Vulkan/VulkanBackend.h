#pragma once
#include <unordered_map>
#include "Windows/BaseWindow.h"
#include "Backends/BaseBackend.h"
#include "Backends/Vulkan/Device.h"
#include "Backends/Vulkan//CommandBuffers/GraphicalCommandBuffer.h"
#include "Backends/Vulkan//Memory/AllocationFactories/VMAAllocationFactory.h"
#include "Backends/Vulkan//Samplers/LinearRepeatSampler.h"
#include "Backends/Vulkan//Pipelines/Pipeline.h"
#include "Backends/Vulkan/GPUResources/GPUImages/GPUImage2D.h"
#include "Backends/Vulkan/GPUResources/GPUImages/GPUCubemap.h"
#include "Backends/Vulkan/Descriptors/DescriptorSets/UniformDescriptorSet.h"
#include "Backends/Vulkan/Descriptors/DescriptorSets/ImageDescriptorSet.h"
#include "Backends/Vulkan/Descriptors/DescriptorSets/StorageBufferDescriptorSet.h"

class VulkanBackend : public BaseBackend {
public:
	VulkanBackend(BaseWindow& window);
	VulkanBackend(VulkanBackend&) = delete;
	virtual ~VulkanBackend();

	VulkanBackend& operator=(VulkanBackend&) = delete;

	virtual const BackendPipelineReference CreatePipeline(PipelineCreateInfo createInfo) override;
	virtual const BackendModelReference CreateModel(CPUBaseModel& model) override;
	virtual const BackendImage2DReference CreateImage2D(CPUImage2D& image) override;
	virtual const BackendCubemapReference CreateCubemap(CPUCubemap& image) override;
	virtual const BackendUniformReference CreateUniform(const std::string uniformId, const uint32_t uniformSize) override;
	virtual const BackendStorageBufferReference CreateStorageBuffer(const std::string storageId, const uint32_t elementSize, const uint32_t maxElements) override;

	virtual void BindPipeline(const BackendPipelineReference shader) override;
	virtual void BindModel(const BackendModelReference model) override;
	virtual void BindImage2D(const uint32_t location, const BackendImage2DReference image) override;
	virtual void BindCubemap(const uint32_t location, const BackendCubemapReference image) override;
	virtual void BindUniform(const uint32_t location, const BackendUniformReference uniform) override;
	virtual void BindStorageBuffer(const uint32_t location, const BackendStorageBufferReference storage);

	virtual void UpdateUniform(const BackendUniformReference uniform, const void* uniformData) override;
	virtual void UpdateStorageBuffer(const BackendStorageBufferReference storage, const void* storageData, const uint32_t nElements) override;

	virtual void BeginFrame() override;
	virtual void Draw() override;
	virtual void EndFrame() override;

	static void FramebufferResizeCallback(void* buffer);

private:
	unsigned int maxFramesInFlight = 2;

	static const std::unordered_map<VertexType, std::unordered_map <uint8_t, VkFormat>> vertexFormatMap;
	static const std::unordered_map<VertexType, std::unordered_map <uint8_t, uint32_t>> vertexSizeMap;

	Device device;
	VMAAllocationFactory allocationFactory;
	LinearRepeatSampler sampler;
	std::vector<GraphicalCommandBuffer* > commandBuffers;
	std::unordered_map<AttachmentType, const BaseDescriptorLayout*> descriptorLayoutMap;
	std::unordered_map <std::string, const Pipeline*> pipelineMap;
	std::unordered_map <std::string, const GPUBaseImage*> imageMap;
	std::unordered_map <std::string, const GPUModel*> modelMap;
	std::unordered_map <std::string, const ImageDescriptorPool*> imageDescriptorPoolMap;
	std::unordered_map <std::string, const ImageDescriptorSet*> imageDescriptorSetsMap;
	std::unordered_map <std::string, const UniformDescriptorPool*> uniformDescriptorPoolMap;
	std::unordered_map <std::string, std::vector<const UniformDescriptorSet*>> uniformDescriptorSetsMap;
	std::unordered_map <std::string, const StorageBufferDescriptorPool*> storageBufferDescriptorPoolMap;
	std::unordered_map <std::string, std::vector<const StorageBufferDescriptorSet*>> storageBufferDescriptorSetsMap;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
};