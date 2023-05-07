#pragma once
#include <unordered_map>
#include "Windows/BaseWindow.h"
#include "Backends/BaseBackend.h"
#include "Backends/Vulkan/Device.h"
#include "Backends/Vulkan//CommandBuffers/GraphicalCommandBuffer.h"
#include "Backends/Vulkan//Memory/AllocationFactories/VMAAllocationFactory.h"
#include "Backends/Vulkan//Samplers/LinearRepeatSampler.h"

#include "Backends/Vulkan//Pipelines/Object3DPipeline.h"
#include "Backends/Vulkan//Pipelines/SkyboxPipeline.h"

class VulkanBackend : public BaseBackend {
public:
	VulkanBackend(const BaseWindow& window);
	VulkanBackend(VulkanBackend&) = delete;
	virtual ~VulkanBackend();

	VulkanBackend& operator=(VulkanBackend&) = delete;

	virtual const ModelReference CreateModel(CPUBaseModel& model) override;
	virtual const ImageReference CreateImage(CPUImage& image) override;
	virtual const UniformReference CreateUniform(const std::string uniformId, const uint32_t uniformSize) override;

	virtual void BindPipeline(const ShaderType shaderType) override;
	virtual void BindModel(const ModelReference model) override;
	virtual void BindImage(const uint32_t location, const ImageReference texture) override;
	virtual void BindUniform(const uint32_t location, const UniformReference uniform) override;

	virtual void UpdateUniform(const UniformReference uniform, const void* uniformData) override;

	virtual void BeginFrame() override;
	virtual void Draw() override;
	virtual void EndFrame() override;

	virtual void Reset() override;

	static void FramebufferResizeCallback(void* buffer);

private:
	struct FrameData {
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};

	struct ModelData {
		glm::mat4 modelMatrix;
	};

	unsigned int maxFramesInFlight = 2;

	Device device;
	VMAAllocationFactory allocationFactory;
	LinearRepeatSampler sampler;
	ImageDescriptorLayout imageDescriptorLayout;
	UniformDescriptorLayout uniformDescriptorLayout;
	const Object3DPipeline object3DPipeline;
	const SkyboxPipeline skyboxPipeline;
	std::vector<GraphicalCommandBuffer* > commandBuffers;
	std::unordered_map <std::string, const GPUImage*> imageMap;
	std::unordered_map <std::string, const GPUModel*> modelMap;
	std::unordered_map <std::string, const ImageDescriptorPool*> imageDescriptorPoolMap;
	std::unordered_map <std::string, const ImageDescriptorSet*> imageDescriptorSetsMap;
	std::unordered_map <std::string, const UniformDescriptorPool*> uniformDescriptorPoolMap;
	std::unordered_map <std::string, std::vector<const UniformDescriptorSet*>> uniformDescriptorSetsMap;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
};