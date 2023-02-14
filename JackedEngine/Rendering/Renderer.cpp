#include "Renderer.h"

Renderer::Renderer(const BaseWindow* const window, const int maxFramesInFlight) :
	maxFramesInFlight(maxFramesInFlight)
{
	device = new Device(window);

	descriptorPool = new Base3DDescriptorPool(device, maxFramesInFlight);
	pipeline = new Pipeline(device, descriptorPool);
	vertexBuffer = new VertexBuffer(device);	
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		commandBuffers.push_back(new CommandBuffer(device));
		descriptorSets.push_back(new Base3DDescriptorSet(device,descriptorPool));
	}
	window->SetBufferResizeCallback(this, Renderer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		delete commandBuffers[i];
		delete descriptorSets[i];
	}
	delete descriptorPool;
	delete pipeline;
	delete vertexBuffer;
	delete device;
}

void Renderer::DrawFrame() {
	descriptorSets[currentFrame]->UpdateDescriptorSet();

	VkResult result = commandBuffers[currentFrame]->PresentCommand(pipeline,vertexBuffer, descriptorSets[currentFrame]);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		framebufferResized = false;
		device->RecreateSwapChain();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}
	currentFrame = (currentFrame + 1) % maxFramesInFlight;
}

void Renderer::Reset() const {
	vkDeviceWaitIdle(*device->GetLogicalDevice());
}

void Renderer::FramebufferResizeCallback(void * buffer) {
	Renderer* renderer = reinterpret_cast<Renderer*>(buffer);
	renderer->framebufferResized = true;
}