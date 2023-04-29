#include "VulkanBackend.h"

VulkanBackend::VulkanBackend(const BaseWindow& window) :
	device(window),
	allocationFactory(device),
	sampler(device),
	frameDescriptorLayout(device),
	frameDescriptorPool(device, maxFramesInFlight),
	materialDescriptorLayout(device),
	object3DPipeline(device, frameDescriptorLayout, materialDescriptorLayout),
	skyboxPipeline(device, frameDescriptorLayout, materialDescriptorLayout)
{
	commandBuffers.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new GraphicalCommandBuffer(device);
	}
	frameDescriptorSets.resize(maxFramesInFlight);
	for (unsigned int i = 0; i < maxFramesInFlight; i++) {
		frameDescriptorSets[i] = new FrameDescriptorSet(device, frameDescriptorLayout, frameDescriptorPool, allocationFactory);
	}
	window.SetBufferResizeCallback(this, VulkanBackend::FramebufferResizeCallback);
}

VulkanBackend::~VulkanBackend() {
	for (auto it = modelMap.begin(); it != modelMap.end(); it++) {
		delete it->second;
	}

	for (auto it = imageMap.begin(); it != imageMap.end(); it++) {
		delete it->second;
	}

	for (unsigned int i = 0; i < maxFramesInFlight; i++) {
		delete frameDescriptorSets[i];
	}

	for (unsigned int i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
	}

	for (auto it = materialDescriptorSetsMap.begin(); it != materialDescriptorSetsMap.end(); it++) {
		delete it->second;
	}

	for (auto it = materialDescriptorPoolMap.begin(); it != materialDescriptorPoolMap.end(); it++) {
		delete it->second;
	}
}

TextureReference VulkanBackend::CreateTexture(CPUImage& cpuImage) {
	if (imageMap.find(cpuImage.GetId()) == imageMap.end()) {
		cpuImage.LoadData();
		imageMap[cpuImage.GetId()] = new GPUImage(allocationFactory, cpuImage);

		materialDescriptorPoolMap[cpuImage.GetId()] = new MaterialDescriptorPool(device, 1);
		materialDescriptorSetsMap[cpuImage.GetId()] = new MaterialDescriptorSet(device, materialDescriptorLayout, *materialDescriptorPoolMap[cpuImage.GetId()], allocationFactory, *imageMap[cpuImage.GetId()], sampler);
	}

	TextureReference reference{};
	reference.id = cpuImage.GetId();
	return reference;
}

ModelReference VulkanBackend::CreateModel(CPUBaseModel& model) {
	if (modelMap.find(model.GetId()) == modelMap.end()) {
		model.LoadData();
		modelMap[model.GetId()] = new GPUModel(allocationFactory, model);
	}
	ModelReference reference{};
	reference.id = model.GetId();
	return reference;
}

void VulkanBackend::BeginFrame(const BaseCameraComponent& camera) {
	VkExtent2D swapChainExtent = device.GetSwapChainExtent();
	commandBuffers[currentFrame]->BeginRenderPass();
	frameDescriptorSets[currentFrame]->UpdateUBO(camera.GetViewMatrix(), camera.GetProjectionMatrix(swapChainExtent.width, swapChainExtent.height));
}

void VulkanBackend::Draw(const ShaderType shaderType, const ModelReference modelReference, const TextureReference textureReference, const void* constData) {
	
	const BasePipeline* pipeline;

	switch (shaderType)
	{
		case OBJECT3D:
			pipeline = &object3DPipeline;
			break;
		case SKYBOX:
			pipeline = &skyboxPipeline;
			break;
		default:
			throw std::runtime_error("Shader type not supported");
	}

	commandBuffers[currentFrame]->Draw(
		*pipeline,
		*modelMap[modelReference.id],
		constData,
		*frameDescriptorSets[currentFrame],
		*materialDescriptorSetsMap[textureReference.id]
	);
}

void VulkanBackend::NextRenderPass() {
	commandBuffers[currentFrame]->NextSubpass();
}

void VulkanBackend::EndFrame() {
	VkResult result = commandBuffers[currentFrame]->EndRenderPass();
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		framebufferResized = false;
		device.RecreateSwapChain();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}
	currentFrame = (currentFrame + 1) % maxFramesInFlight;
}

void VulkanBackend::FramebufferResizeCallback(void* buffer) {
	VulkanBackend* vulkanBackend = reinterpret_cast<VulkanBackend*>(buffer);
	vulkanBackend->framebufferResized = true;
}

void VulkanBackend::Reset() {
	vkDeviceWaitIdle(device.GetLogicalDevice());
}