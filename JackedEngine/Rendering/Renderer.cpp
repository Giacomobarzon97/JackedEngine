#include "Renderer.h"

Renderer::Renderer(const BaseWindow& window, const BaseCameraObject& camera) :
	camera(camera),
	device(window),
	descriptorPool(device, maxFramesInFlight),
	pipeline(device, descriptorPool)
{
	commandBuffers.resize(maxFramesInFlight);
	descriptorSets.resize(maxFramesInFlight);

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers[i] = new CommandBuffer(device);
		descriptorSets[i] = new Base3DDescriptorSet(device,descriptorPool);
	}
	window.SetBufferResizeCallback(this, Renderer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
		delete descriptorSets[i];
	}
}


void Renderer::DrawObject(RenderableObject& object) {
	VertexBuffer* vertexBuffer = new VertexBuffer(device,object.GetModel());

	descriptorSets[currentFrame]->UpdateDescriptorSet(camera, object);

	VkResult result = commandBuffers[currentFrame]->PresentCommand(pipeline, *vertexBuffer, *descriptorSets[currentFrame]);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		framebufferResized = false;
		device.RecreateSwapChain();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}
	currentFrame = (currentFrame + 1) % maxFramesInFlight;
	vkDeviceWaitIdle(device.GetLogicalDevice());
	delete vertexBuffer;
}

void Renderer::Reset() const {
	vkDeviceWaitIdle(device.GetLogicalDevice());
}

void Renderer::FramebufferResizeCallback(void * buffer) {
	Renderer* renderer = reinterpret_cast<Renderer*>(buffer);
	renderer->framebufferResized = true;
}