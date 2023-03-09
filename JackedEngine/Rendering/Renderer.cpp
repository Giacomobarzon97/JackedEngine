#include "Renderer.h"

Renderer::Renderer(const BaseWindow& window, const BaseCameraObject& camera) :
	camera(camera),
	device(window),
	imageDescriptorPool(device, maxFramesInFlight),
	uboDescriptorPool(device, maxFramesInFlight),
	pipeline(device, uboDescriptorPool, imageDescriptorPool),
	allocationFactory(device),
	model(allocationFactory, "../Assets/Models/viking_room.obj"),
	imageDescriptorSet(device, imageDescriptorPool, "../Assets/Textures/viking_room.png")
{
	commandBuffers.resize(maxFramesInFlight);
	uboDescriptorSets.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new Graphical3DCommandBuffer(device);
		uboDescriptorSets[i] = new UBODescriptorSet(device, uboDescriptorPool, allocationFactory);
	}
	window.SetBufferResizeCallback(this, Renderer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
		delete uboDescriptorSets[i];
	}
}


void Renderer::DrawObject(RenderableObject& object) {
	uboDescriptorSets[currentFrame]->UpdateDescriptorSet(camera.GetViewProjectionMatrix() * object.GetModelMatrix());

	VkResult result = commandBuffers[currentFrame]->PresentCommand(pipeline, model, *uboDescriptorSets[currentFrame], imageDescriptorSet);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		framebufferResized = false;
		device.RecreateSwapChain();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}
	currentFrame = (currentFrame + 1) % maxFramesInFlight;
	vkDeviceWaitIdle(device.GetLogicalDevice());

}

void Renderer::Reset() const {
	vkDeviceWaitIdle(device.GetLogicalDevice());
}

void Renderer::FramebufferResizeCallback(void * buffer) {
	Renderer* renderer = reinterpret_cast<Renderer*>(buffer);
	renderer->framebufferResized = true;
}