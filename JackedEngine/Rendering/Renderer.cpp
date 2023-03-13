#include "Renderer.h"

Renderer::Renderer(const BaseWindow& window, const BaseCameraObject& camera) :
	camera(camera),
	device(window),
	objectDescriptorPool(device, maxFramesInFlight),
	frameDescriptorPool(device, maxFramesInFlight),
	pipeline(device, frameDescriptorPool, objectDescriptorPool),
	allocationFactory(device),
	model(allocationFactory, CPUModel("../Assets/Models/viking_room.obj")),
	image(allocationFactory, CPUImage("../Assets/Textures/viking_room.png")),
	objectDescriptorSet(device, objectDescriptorPool, image)
{
	commandBuffers.resize(maxFramesInFlight);
	frameDescriptorSets.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new Graphical3DCommandBuffer(device);
		frameDescriptorSets[i] = new FrameDescriptorSet(device, frameDescriptorPool, allocationFactory);
	}
	window.SetBufferResizeCallback(this, Renderer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
		delete frameDescriptorSets[i];
	}
}


void Renderer::DrawObject(RenderableObject& object) {
	frameDescriptorSets[currentFrame]->UpdateDescriptorSet(camera.GetViewProjectionMatrix() * object.GetModelMatrix());

	VkResult result = commandBuffers[currentFrame]->PresentCommand(pipeline, model, *frameDescriptorSets[currentFrame], objectDescriptorSet);
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