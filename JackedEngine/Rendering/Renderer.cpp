#include "Renderer.h"

Renderer::Renderer(BaseWindow* window, int maxFramesInFlight) {
	uint32_t windowExtensionCount = 0;
	const char** windowExtensions = window->GetRequiredExtensions(&windowExtensionCount);
	std::vector<const char*> extensions(windowExtensions, windowExtensions + windowExtensionCount);

	instance = new Instance(window->GetWindowName(), extensions);
	window->InitiWindowSurface(instance->GetVkInstance(), instance->GetVkSurface());
	device = new Device(instance);
	swapChain = new SwapChain(instance, device, window);
	pipeline = new Pipeline(device, swapChain);
	commandBuffer = new CommandBuffer(device, swapChain, maxFramesInFlight);
	window->SetBufferResizeCallback(commandBuffer, CommandBuffer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	delete commandBuffer;
	delete pipeline;
	delete swapChain;
	delete device;
	delete instance;
}

void Renderer::DrawFrame() {
	commandBuffer->PresentCommand(pipeline);
}

void Renderer::Reset() {
	vkDeviceWaitIdle(*device->GetLogicalDevice());
}
