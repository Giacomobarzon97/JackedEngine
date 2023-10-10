#include "VulkanBackend.h"

std::unordered_map<VertexType, std::unordered_map <uint8_t, VkFormat>> initVertexFormatMap() {
	std::unordered_map<VertexType, std::unordered_map <uint8_t, VkFormat>> formatMap;
	formatMap[VertexType::FLOAT_32] = std::unordered_map <uint8_t, VkFormat>();
	formatMap[VertexType::INT_32] = std::unordered_map <uint8_t, VkFormat>();

	formatMap[VertexType::FLOAT_32][1] = VK_FORMAT_R32_SFLOAT;
	formatMap[VertexType::FLOAT_32][2] = VK_FORMAT_R32G32_SFLOAT;
	formatMap[VertexType::FLOAT_32][3] = VK_FORMAT_R32G32B32_SFLOAT;
	formatMap[VertexType::FLOAT_32][4] = VK_FORMAT_R32G32B32A32_SFLOAT;

	formatMap[VertexType::INT_32][1] = VK_FORMAT_R32_SINT;
	formatMap[VertexType::INT_32][2] = VK_FORMAT_R32G32_SINT;
	formatMap[VertexType::INT_32][3] = VK_FORMAT_R32G32B32_SINT;
	formatMap[VertexType::INT_32][4] = VK_FORMAT_R32G32B32A32_SINT;

	return formatMap;
}

std::unordered_map<VertexType, std::unordered_map <uint8_t, uint32_t>> initVertexSizeMap() {
	std::unordered_map<VertexType, std::unordered_map <uint8_t, uint32_t>> sizeMap;

	sizeMap[VertexType::FLOAT_32] = std::unordered_map <uint8_t, uint32_t>();
	sizeMap[VertexType::INT_32] = std::unordered_map <uint8_t, uint32_t>();

	sizeMap[VertexType::FLOAT_32][1] = 4;
	sizeMap[VertexType::FLOAT_32][2] = 8;
	sizeMap[VertexType::FLOAT_32][3] = 12;
	sizeMap[VertexType::FLOAT_32][4] = 16;

	sizeMap[VertexType::INT_32][1] = 4;
	sizeMap[VertexType::INT_32][2] = 8;
	sizeMap[VertexType::INT_32][3] = 12;
	sizeMap[VertexType::INT_32][4] = 16;

	return sizeMap;
}

const std::unordered_map<VertexType, std::unordered_map <uint8_t, VkFormat>> VulkanBackend::vertexFormatMap = initVertexFormatMap();
const std::unordered_map<VertexType, std::unordered_map <uint8_t, uint32_t>> VulkanBackend::vertexSizeMap = initVertexSizeMap();


VulkanBackend::VulkanBackend(BaseWindow& window) :
	device(window),
	allocationFactory(device),
	sampler(device)
{
	descriptorLayoutMap[AttachmentType::IMAGE] = new ImageDescriptorLayout(device);
	descriptorLayoutMap[AttachmentType::UNIFORM] = new UniformDescriptorLayout(device);

	commandBuffers.resize(maxFramesInFlight);
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new GraphicalCommandBuffer(device);
	}
	window.SetBufferResizeCallback(this, VulkanBackend::FramebufferResizeCallback);
}

VulkanBackend::~VulkanBackend() {
	vkDeviceWaitIdle(device.GetLogicalDevice());

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
	
	for (auto it = pipelineMap.begin(); it != pipelineMap.end(); it++) {
		delete it->second;
	}

	for (auto it = descriptorLayoutMap.begin(); it != descriptorLayoutMap.end(); it++) {
		delete it->second;
	}
}

const BackendPipelineReference VulkanBackend::CreatePipeline(PipelineCreateInfo createInfo) {
	if (pipelineMap.find(createInfo.id) != pipelineMap.end()) {
		throw std::runtime_error("Pipeline already created with the same Id");
	}

	std::vector<const BaseDescriptorLayout*> layouts(createInfo.attachments.size());
	for (unsigned int i = 0; i < createInfo.attachments.size(); i++) {
		if (descriptorLayoutMap.find(createInfo.attachments[i]) == descriptorLayoutMap.end()) {
			throw std::runtime_error("Attachment type not supported");
		}
		layouts[i] = descriptorLayoutMap[createInfo.attachments[i]];
	}

	std::vector<uint32_t> vertexSizes(createInfo.vertices.size());
	std::vector<VkFormat> vertexFormats(createInfo.vertices.size());

	for (unsigned int i = 0; i < createInfo.vertices.size(); i++) {
		if (
			vertexSizeMap.find(createInfo.vertices[i].type) == vertexSizeMap.end() ||
			vertexSizeMap.at(createInfo.vertices[i].type).find(createInfo.vertices[i].size) == vertexSizeMap.at(createInfo.vertices[i].type).end() ||
			vertexFormatMap.find(createInfo.vertices[i].type) == vertexFormatMap.end() ||
			vertexFormatMap.at(createInfo.vertices[i].type).find(createInfo.vertices[i].size) == vertexFormatMap.at(createInfo.vertices[i].type).end()
		) {
			throw std::runtime_error("Vertex configuration not supported");
		}

		vertexSizes[i] = vertexSizeMap.at(createInfo.vertices[i].type).at(createInfo.vertices[i].size);
		vertexFormats[i] = vertexFormatMap.at(createInfo.vertices[i].type).at(createInfo.vertices[i].size);
	}

	pipelineMap[createInfo.id] = new Pipeline(
		device,
		createInfo.vertexShader,
		createInfo.fragmentShader,
		layouts,
		vertexSizes,
		vertexFormats
	);

	return BackendPipelineReference(createInfo.id);
}

const BackendModelReference VulkanBackend::CreateModel(CPUBaseModel& model) {
	if (modelMap.find(model.GetId()) == modelMap.end()) {
		model.LoadData();
		modelMap[model.GetId()] = new GPUModel(allocationFactory, model);
	}
	return BackendModelReference(model.GetId());
}

const BackendImage2DReference VulkanBackend::CreateImage2D(CPUImage2D& cpuImage) {
	if (imageMap.find(cpuImage.GetId()) == imageMap.end()) {
		cpuImage.LoadData();
		imageMap[cpuImage.GetId()] = new GPUImage2D(allocationFactory, cpuImage);

		imageDescriptorPoolMap[cpuImage.GetId()] = new ImageDescriptorPool(device, 1);
		imageDescriptorSetsMap[cpuImage.GetId()] = new ImageDescriptorSet(
			device, 
			*static_cast<const ImageDescriptorLayout*>(descriptorLayoutMap[AttachmentType::IMAGE]),
			*imageDescriptorPoolMap[cpuImage.GetId()], 
			allocationFactory, 
			*imageMap[cpuImage.GetId()], 
			sampler
		);
	}

	return BackendImage2DReference(cpuImage.GetId());
}

const BackendCubemapReference VulkanBackend::CreateCubemap(CPUCubemap& cpuImage) {
	if (imageMap.find(cpuImage.GetId()) == imageMap.end()) {
		cpuImage.LoadData();
		imageMap[cpuImage.GetId()] = new GPUCubemap(allocationFactory, cpuImage);

		imageDescriptorPoolMap[cpuImage.GetId()] = new ImageDescriptorPool(device, 1);
		imageDescriptorSetsMap[cpuImage.GetId()] = new ImageDescriptorSet(
			device,
			*static_cast<const ImageDescriptorLayout*>(descriptorLayoutMap[AttachmentType::IMAGE]),
			*imageDescriptorPoolMap[cpuImage.GetId()],
			allocationFactory,
			*imageMap[cpuImage.GetId()],
			sampler
		);
	}

	return BackendCubemapReference(cpuImage.GetId());
}

const BackendUniformReference VulkanBackend::CreateUniform(std::string uniformId, const uint32_t uniformSize) {
	if (uniformDescriptorPoolMap.find(uniformId) != uniformDescriptorPoolMap.end()) {
		throw std::runtime_error("Uniform already created with the same Id");
	}

	uniformDescriptorPoolMap[uniformId] = new UniformDescriptorPool(device, maxFramesInFlight);
	uniformDescriptorSetsMap[uniformId] = std::vector<const UniformDescriptorSet*>(maxFramesInFlight);
	for (unsigned int i = 0; i < maxFramesInFlight; i++) {
		uniformDescriptorSetsMap[uniformId][i] = new UniformDescriptorSet(
			device, 
			*static_cast<const UniformDescriptorLayout*>(descriptorLayoutMap[AttachmentType::UNIFORM]),
			*uniformDescriptorPoolMap[uniformId], 
			allocationFactory, 
			uniformSize
		);
	}

	return BackendUniformReference(uniformId);
}

void VulkanBackend::BindPipeline(const BackendPipelineReference shader) {
	if (pipelineMap.find(shader.GetId()) == pipelineMap.end()) {
		throw std::runtime_error("Pipeline does not exist");
	}
	commandBuffers[currentFrame]->BindPipeline(*pipelineMap[shader.GetId()]);
}

void VulkanBackend::UpdateUniform(const BackendUniformReference uniform, const void* uniformData) {
	if (uniformDescriptorSetsMap.find(uniform.GetId()) == uniformDescriptorSetsMap.end()) {
		throw std::runtime_error("Uniform does not exist");
	}
	uniformDescriptorSetsMap[uniform.GetId()][currentFrame]->UpdateUniform(uniformData);
}

void VulkanBackend::BindModel(const BackendModelReference model) {
	if (modelMap.find(model.GetId()) == modelMap.end()) {
		throw std::runtime_error("Model does not exist");
	}
	commandBuffers[currentFrame]->BindModel(*modelMap[model.GetId()]);
}

void VulkanBackend::BindImage2D(const uint32_t location, const BackendImage2DReference image) {
	if (imageDescriptorSetsMap.find(image.GetId()) == imageDescriptorSetsMap.end()) {
		throw std::runtime_error("Image does not exist");
	}
	commandBuffers[currentFrame]->BindDescriptorSet(*imageDescriptorSetsMap[image.GetId()], location);
}

void VulkanBackend::BindCubemap(const uint32_t location, const BackendCubemapReference image) {
	if (imageDescriptorSetsMap.find(image.GetId()) == imageDescriptorSetsMap.end()) {
		throw std::runtime_error("Image does not exist");
	}
	commandBuffers[currentFrame]->BindDescriptorSet(*imageDescriptorSetsMap[image.GetId()], location);
}

void VulkanBackend::BindUniform(const uint32_t location, const BackendUniformReference uniform) {
	if (uniformDescriptorSetsMap.find(uniform.GetId()) == uniformDescriptorSetsMap.end()) {
		throw std::runtime_error("Uniform does not exist");
	}
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