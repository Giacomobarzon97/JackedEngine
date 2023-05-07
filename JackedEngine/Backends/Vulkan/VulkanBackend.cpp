#include "VulkanBackend.h"

VulkanBackend::VulkanBackend(const BaseWindow& window) :
	device(window),
	allocationFactory(device),
	sampler(device),
	uniformDescriptorLayout(device),
	imageDescriptorLayout(device),
	object3DPipeline(device, uniformDescriptorLayout, imageDescriptorLayout),
	skyboxPipeline(device, uniformDescriptorLayout, imageDescriptorLayout)
{
	commandBuffers.resize(maxFramesInFlight);
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new GraphicalCommandBuffer(device);
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
		delete commandBuffers[i];
	}

	for (auto it = imageDescriptorSetsMap.begin(); it != imageDescriptorSetsMap.end(); it++) {
		delete it->second;
	}

	for (auto it = imageDescriptorPoolMap.begin(); it != imageDescriptorPoolMap.end(); it++) {
		delete it->second;
	}

	for (auto it = uniformDescriptorSetsMap.begin(); it != uniformDescriptorSetsMap.end(); it++) {
		for (unsigned int i = 0; i < it->second.size(); i++) {
			delete it->second[i];
		}
	}

	for (auto it = uniformDescriptorPoolMap.begin(); it != uniformDescriptorPoolMap.end(); it++) {
		delete it->second;
	}
}

const ModelReference VulkanBackend::CreateModel(CPUBaseModel& model) {
	if (modelMap.find(model.GetId()) == modelMap.end()) {
		model.LoadData();
		modelMap[model.GetId()] = new GPUModel(allocationFactory, model);
	}
	ModelReference reference(model.GetId());
	return reference;
}

const ImageReference VulkanBackend::CreateImage(CPUImage& cpuImage) {
	if (imageMap.find(cpuImage.GetId()) == imageMap.end()) {
		cpuImage.LoadData();
		imageMap[cpuImage.GetId()] = new GPUImage(allocationFactory, cpuImage);

		imageDescriptorPoolMap[cpuImage.GetId()] = new ImageDescriptorPool(device, 1);
		imageDescriptorSetsMap[cpuImage.GetId()] = new ImageDescriptorSet(device, imageDescriptorLayout, *imageDescriptorPoolMap[cpuImage.GetId()], allocationFactory, *imageMap[cpuImage.GetId()], sampler);
	}

	ImageReference reference(cpuImage.GetId());
	return reference;
}

const UniformReference VulkanBackend::CreateUniform(std::string uniformId, const uint32_t uniformSize) {
	if (uniformDescriptorPoolMap.find(uniformId) != uniformDescriptorPoolMap.end()) {
		throw std::runtime_error("Uniform already created with the same Id");
	}

	uniformDescriptorPoolMap[uniformId] = new UniformDescriptorPool(device, maxFramesInFlight);
	uniformDescriptorSetsMap[uniformId] = std::vector<const UniformDescriptorSet*>(maxFramesInFlight);
	for (unsigned int i = 0; i < maxFramesInFlight; i++) {
		uniformDescriptorSetsMap[uniformId][i] = new UniformDescriptorSet(device, uniformDescriptorLayout, *uniformDescriptorPoolMap[uniformId], allocationFactory, uniformSize);
	}

	UniformReference reference(uniformId);
	return reference;
}

void VulkanBackend::BindPipeline(const ShaderType shaderType) {
	const BasePipeline* pipeline;

	//TODO: Substitute this switch with a map to find correct pipeline in costant time and improve performances
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

	commandBuffers[currentFrame]->BindPipeline(*pipeline);
}

void VulkanBackend::UpdateUniform(const UniformReference uniform, const void* uniformData) {
	uniformDescriptorSetsMap[uniform.GetId()][currentFrame]->UpdateUniform(uniformData);
}

void VulkanBackend::BindModel(const ModelReference model) {
	commandBuffers[currentFrame]->BindModel(*modelMap[model.GetId()]);
}

void VulkanBackend::BindImage(const uint32_t location, const ImageReference texture) {
	commandBuffers[currentFrame]->BindDescriptorSet(*imageDescriptorSetsMap[texture.GetId()], location);
}

void VulkanBackend::BindUniform(const uint32_t location, const UniformReference uniform) {
	commandBuffers[currentFrame]->BindDescriptorSet(*uniformDescriptorSetsMap[uniform.GetId()][currentFrame], location);
}

void VulkanBackend::BeginFrame() {
	commandBuffers[currentFrame]->BeginRenderPass();
}

void VulkanBackend::Draw() {
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