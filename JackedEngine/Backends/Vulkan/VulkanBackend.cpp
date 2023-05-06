#include "VulkanBackend.h"

VulkanBackend::VulkanBackend(const BaseWindow& window) :
	device(window),
	allocationFactory(device),
	sampler(device),
	uniformDescriptorLayout(device),
	imageDescriptorLayout(device),
	frameDataDescriptorPool(device, maxFramesInFlight),
	modelDataDescriptorPool(device, maxFramesInFlight),
	object3DPipeline(device, uniformDescriptorLayout, imageDescriptorLayout),
	skyboxPipeline(device, uniformDescriptorLayout, imageDescriptorLayout)
{
	commandBuffers.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new GraphicalCommandBuffer(device);
	}
	frameDataDescriptorSets.resize(maxFramesInFlight);
	for (unsigned int i = 0; i < maxFramesInFlight; i++) {
		frameDataDescriptorSets[i] = new UniformDescriptorSet(device, uniformDescriptorLayout, frameDataDescriptorPool, allocationFactory, sizeof(FrameData));
	}
	modelDataDescriptorSets.resize(maxFramesInFlight);
	for (unsigned int i = 0; i < maxFramesInFlight; i++) {
		modelDataDescriptorSets[i] = new UniformDescriptorSet(device, uniformDescriptorLayout, modelDataDescriptorPool, allocationFactory, sizeof(ModelData));
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
		delete frameDataDescriptorSets[i];
	}

	for (unsigned int i = 0; i < maxFramesInFlight; i++) {
		delete modelDataDescriptorSets[i];
	}

	for (unsigned int i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
	}

	for (auto it = imageDescriptorSetsMap.begin(); it != imageDescriptorSetsMap.end(); it++) {
		delete it->second;
	}

	for (auto it = imageDescriptorPoolMap.begin(); it != imageDescriptorPoolMap.end(); it++) {
		delete it->second;
	}
}

TextureReference VulkanBackend::CreateTexture(CPUImage& cpuImage) {
	if (imageMap.find(cpuImage.GetId()) == imageMap.end()) {
		cpuImage.LoadData();
		imageMap[cpuImage.GetId()] = new GPUImage(allocationFactory, cpuImage);

		imageDescriptorPoolMap[cpuImage.GetId()] = new ImageDescriptorPool(device, 1);
		imageDescriptorSetsMap[cpuImage.GetId()] = new ImageDescriptorSet(device, imageDescriptorLayout, *imageDescriptorPoolMap[cpuImage.GetId()], allocationFactory, *imageMap[cpuImage.GetId()], sampler);
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
	FrameData frameData{};
	frameData.projectionMatrix = camera.GetProjectionMatrix(swapChainExtent.width, swapChainExtent.height);
	frameData.viewMatrix = camera.GetViewMatrix();
	frameDataDescriptorSets[currentFrame]->UpdateUniform(&frameData);
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

	modelDataDescriptorSets[currentFrame]->UpdateUniform(constData);

	commandBuffers[currentFrame]->BindPipeline(*pipeline);
	commandBuffers[currentFrame]->BindModel(*modelMap[modelReference.id]);
	commandBuffers[currentFrame]->BindDescriptorSet(*frameDataDescriptorSets[currentFrame], 0);
	commandBuffers[currentFrame]->BindDescriptorSet(*modelDataDescriptorSets[currentFrame], 1);
	commandBuffers[currentFrame]->BindDescriptorSet(*imageDescriptorSetsMap[textureReference.id], 2);

	commandBuffers[currentFrame]->Draw();
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