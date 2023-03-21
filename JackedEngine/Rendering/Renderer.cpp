#include "Renderer.h"

Renderer::Renderer(const BaseWindow& window, const BaseCameraObject& camera) :
	camera(camera),
	device(window),
	allocationFactory(device),
	sampler(device),
	renderingManager(device, allocationFactory, sampler, maxFramesInFlight),
	pipeline(device, renderingManager.GetFrameDescriptorLayout(), renderingManager.GetObjectDescriptorLayout())
{
	commandBuffers.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new GraphicalCommandBuffer(device);
	}
	window.SetBufferResizeCallback(this, Renderer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
	}
}


void Renderer::DrawObject(std::vector<RenderableObject> objects) {
	for (RenderableObject object : objects) {
		const FrameDescriptorSet& frameDescriptorSet = renderingManager.GetFrameDescriptor(currentFrame);
		const ObjectDescriptorSet& objectDescriptorSet = renderingManager.CreateOrGetObjectDescriptor(object.GetName(), object.GetTexturePath(), currentFrame);

		frameDescriptorSet.UpdateUBO(camera.GetViewMatrix(), camera.GetProjectionMatrix());
		objectDescriptorSet.UpdateModelMatrix(object.GetModelMatrix());

		VkResult result = commandBuffers[currentFrame]->DrawObject(
			pipeline,
			renderingManager.CreateOrGetModel(object.GetModelPath()),
			frameDescriptorSet,
			objectDescriptorSet
		);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
			framebufferResized = false;
			device.RecreateSwapChain();
		}
		else if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image!");
		}
		currentFrame = (currentFrame + 1) % maxFramesInFlight;
	}
}

void Renderer::Reset() const {
	vkDeviceWaitIdle(device.GetLogicalDevice());
}

void Renderer::FramebufferResizeCallback(void * buffer) {
	Renderer* renderer = reinterpret_cast<Renderer*>(buffer);
	renderer->framebufferResized = true;
}