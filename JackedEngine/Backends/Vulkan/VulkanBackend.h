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


	virtual TextureReference CreateTexture(CPUImage& image) override;
	virtual ModelReference CreateModel(CPUBaseModel& model) override;

	virtual void BeginFrame(const BaseCameraComponent& camera) override;
	virtual void Draw(const ShaderType shaderType, const ModelReference modelReference, const TextureReference textureReference, const void * constData) override;
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
	std::unordered_map<std::string, const GPUImage*> imageMap;
	std::unordered_map <std::string, const GPUModel*> modelMap;
	UniformDescriptorPool frameDataDescriptorPool;
	std::vector<const UniformDescriptorSet*> frameDataDescriptorSets;
	UniformDescriptorPool modelDataDescriptorPool;
	std::vector<const UniformDescriptorSet*> modelDataDescriptorSets;
	std::unordered_map <std::string, const ImageDescriptorPool*> imageDescriptorPoolMap;
	std::unordered_map <std::string,const ImageDescriptorSet*> imageDescriptorSetsMap;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
};