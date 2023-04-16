#include "Renderer.h"

Renderer::Renderer(const BaseWindow& window, const BaseCameraObject& camera) :
	camera(camera),
	device(window),
	allocationFactory(device),
	sampler(device),
	renderingManager(device, allocationFactory, sampler, maxFramesInFlight),
	object3DPipeline(device, renderingManager.GetFrameDescriptorLayout(), renderingManager.GetObjectDescriptorLayout()),
	skyboxModel(
		allocationFactory,
		CPUCubeModel()
	),
	skyboxDescriptorPool(device,1),
	skyboxDescriptorLayout(device),
	skyboxPipeline(device, renderingManager.GetFrameDescriptorLayout(), skyboxDescriptorLayout)
{
	commandBuffers.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new GraphicalCommandBuffer(device);
	}
	window.SetBufferResizeCallback(this, Renderer::FramebufferResizeCallback);

	CPUImage cpuCubemap(
		std::vector<std::string> {
		"../Assets/Textures/Skybox/front.png",
			"../Assets/Textures/Skybox/back.png",
			"../Assets/Textures/Skybox/top.png",
			"../Assets/Textures/Skybox/bottom.png",
			"../Assets/Textures/Skybox/right.png",
			"../Assets/Textures/Skybox/left.png"
		},
		CUBEMAP
	);
	cpuCubemap.LoadData();
	cubemap = new GPUImage(allocationFactory, cpuCubemap);

	skyboxDescriptorSet = new MaterialDescriptorSet(device, skyboxDescriptorLayout, skyboxDescriptorPool, allocationFactory, *cubemap, sampler);
}

Renderer::~Renderer() {
	delete cubemap;
	delete skyboxDescriptorSet;

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
	}
}


void Renderer::DrawObject(std::vector<RenderableObject> objects) {

	commandBuffers[currentFrame]->BeginRenderPass();
	const FrameDescriptorSet& frameDescriptorSet = renderingManager.GetFrameDescriptor(currentFrame);

	glm::mat4 identity;

	commandBuffers[currentFrame]->Draw(skyboxPipeline, skyboxModel, &identity, frameDescriptorSet, *skyboxDescriptorSet);

	commandBuffers[currentFrame]->NextSubpass();
	
	for (RenderableObject object : objects) {
		const MaterialDescriptorSet& objectDescriptorSet = renderingManager.CreateOrGetObjectDescriptor(object.GetName(), object.GetTexturePath(), currentFrame);

		VkExtent2D swapChainExtent = device.GetSwapChainExtent();

		frameDescriptorSet.UpdateUBO(camera.GetViewMatrix(), camera.GetProjectionMatrix(swapChainExtent.width, swapChainExtent.height));

		glm::mat4 modelMat = object.GetModelMatrix();

		commandBuffers[currentFrame]->Draw(
			object3DPipeline,
			renderingManager.CreateOrGetModel(object.GetModelPath()),
			&modelMat,
			frameDescriptorSet,
			objectDescriptorSet
		);
	}

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

void Renderer::Reset() const {
	vkDeviceWaitIdle(device.GetLogicalDevice());
}

void Renderer::FramebufferResizeCallback(void * buffer) {
	Renderer* renderer = reinterpret_cast<Renderer*>(buffer);
	renderer->framebufferResized = true;
}
