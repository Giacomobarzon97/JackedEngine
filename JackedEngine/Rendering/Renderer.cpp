#include "Renderer.h"

Renderer::Renderer(const BaseWindow& window, const BaseCameraObject& camera) :
	camera(camera),
	device(window),
	allocationFactory(device),
	sampler(device),
	renderingManager(device, allocationFactory, sampler, maxFramesInFlight),
	object3DPipeline(device, renderingManager.GetFrameDescriptorLayout(), renderingManager.GetObjectDescriptorLayout()),
	cubemap(
		allocationFactory,
		CPUImage("../Assets/Textures/Skybox/front.png"),
		CPUImage("../Assets/Textures/Skybox/back.png"),
		CPUImage("../Assets/Textures/Skybox/top.png"),
		CPUImage("../Assets/Textures/Skybox/bottom.png"),
		CPUImage("../Assets/Textures/Skybox/right.png"),
		CPUImage("../Assets/Textures/Skybox/left.png")
	),
	skyboxDescriptorPool(device,1),
	skyboxDescriptorLayout(device),
	skyboxDescriptorSet(device, skyboxDescriptorLayout, skyboxDescriptorPool, allocationFactory, cubemap, sampler),
	skyboxPipeline(device, renderingManager.GetFrameDescriptorLayout(), skyboxDescriptorLayout)
{
	commandBuffers.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new GraphicalCommandBuffer(device, object3DPipeline, skyboxPipeline);
	}
	window.SetBufferResizeCallback(this, Renderer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
	}
}


void Renderer::DrawObject(std::vector<RenderableObject> objects) {

	commandBuffers[currentFrame]->BeginRenderPass();
	const FrameDescriptorSet& frameDescriptorSet = renderingManager.GetFrameDescriptor(currentFrame);

	for (RenderableObject object : objects) {
		const ObjectDescriptorSet& objectDescriptorSet = renderingManager.CreateOrGetObjectDescriptor(object.GetName(), object.GetTexturePath(), currentFrame);

		VkExtent2D swapChainExtent = device.GetSwapChainExtent();

		frameDescriptorSet.UpdateUBO(camera.GetViewMatrix(), camera.GetProjectionMatrix(swapChainExtent.width, swapChainExtent.height));
		objectDescriptorSet.UpdateModelMatrix(object.GetModelMatrix());

		commandBuffers[currentFrame]->Draw(
			renderingManager.CreateOrGetModel(object.GetModelPath()),
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
