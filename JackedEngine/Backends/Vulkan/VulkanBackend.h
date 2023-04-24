#pragma once
#include <unordered_map>
#include "Windows/BaseWindow.h"
#include "Backends/BaseBackend.h"
#include "Backends/Vulkan/Device.h"
#include "Backends/Vulkan//CommandBuffers/GraphicalCommandBuffer.h"
#include "Backends/Vulkan//Memory/AllocationFactories/VMAAllocationFactory.h"
#include "Backends/Vulkan//Samplers/LinearRepeatSampler.h"

#include "Scene/Components/Cameras/BaseCameraComponent.h"
#include "Backends/Vulkan//Pipelines/Object3DPipeline.h"
#include "Backends/Vulkan//Pipelines/SkyboxPipeline.h"

class VulkanBackend : public BaseBackend {
public:
	VulkanBackend(const BaseWindow& window, const BaseCameraComponent& camera);
	VulkanBackend(VulkanBackend&) = delete;
	virtual ~VulkanBackend();

	VulkanBackend& operator=(VulkanBackend&) = delete;


	virtual TextureReference CreateTexture(CPUImage& image) override;
	virtual ModelReference CreateModel(CPUBaseModel& model) override;

	virtual void BeginFrame() override;
	virtual void Draw(const ShaderType shaderType, const ModelReference modelReference, const TextureReference textureReference, const void * constData) override;
	virtual void NextRenderPass() override;
	virtual void EndFrame() override;

	virtual void Reset() override;

	static void FramebufferResizeCallback(void* buffer);

private:
	unsigned int maxFramesInFlight = 2;

	const BaseCameraComponent& camera;
	Device device;
	VMAAllocationFactory allocationFactory;
	LinearRepeatSampler sampler;
	MaterialDescriptorLayout materialDescriptorLayout;
	FrameDescriptorLayout frameDescriptorLayout;
	const Object3DPipeline object3DPipeline;
	const SkyboxPipeline skyboxPipeline;
	std::vector<GraphicalCommandBuffer* > commandBuffers;
	std::unordered_map<std::string, const GPUImage*> imageMap;
	std::unordered_map <std::string, const GPUModel*> modelMap;
	FrameDescriptorPool frameDescriptorPool;
	std::vector<const FrameDescriptorSet*> frameDescriptorSets;
	std::unordered_map <std::string, const MaterialDescriptorPool*> materialDescriptorPoolMap;
	std::unordered_map <std::string,const MaterialDescriptorSet*> materialDescriptorSetsMap;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
};