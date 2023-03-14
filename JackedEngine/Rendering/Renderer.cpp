#include "Renderer.h"

Renderer::Renderer(const BaseWindow& window, const BaseCameraObject& camera) :
	camera(camera),
	device(window),
	frameDescriptorLayout(device),
	objectDescriptorLayout(device),
	objectDescriptorPool(device, maxFramesInFlight),
	frameDescriptorPool(device, maxFramesInFlight),
	pipeline(device, frameDescriptorLayout, objectDescriptorLayout),
	allocationFactory(device),
	model(allocationFactory, CPUModel("../Assets/Models/viking_room.obj")),
	image(allocationFactory, CPUImage("../Assets/Textures/viking_room.png"))
{
	commandBuffers.resize(maxFramesInFlight);
	frameDescriptorSets.resize(maxFramesInFlight);
	objectDescriptorSets.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new Graphical3DCommandBuffer(device);
		frameDescriptorSets[i] = new FrameDescriptorSet(device, frameDescriptorLayout, frameDescriptorPool, allocationFactory);
		objectDescriptorSets[i] = new ObjectDescriptorSet(device, objectDescriptorLayout, objectDescriptorPool, allocationFactory, image);
	}
	window.SetBufferResizeCallback(this, Renderer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
		delete frameDescriptorSets[i];
		delete objectDescriptorSets[i];
	}
}


void Renderer::DrawObject(RenderableObject& object) {
	frameDescriptorSets[currentFrame]->UpdateProjectionViewMatrix(camera.GetViewProjectionMatrix());
	objectDescriptorSets[currentFrame]->UpdateModelMatrix(object.GetModelMatrix());

	VkResult result = commandBuffers[currentFrame]->PresentCommand(pipeline, model, *frameDescriptorSets[currentFrame], *objectDescriptorSets[currentFrame]);
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