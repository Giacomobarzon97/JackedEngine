#include "Renderer.h"

Renderer::Renderer(BaseWindow* window, int maxFramesInFlight) {
	uint32_t windowExtensionCount = 0;
	const char** windowExtensions = window->GetRequiredExtensions(&windowExtensionCount);
	std::vector<const char*> extensions(windowExtensions, windowExtensions + windowExtensionCount);

	instance = new Instance(window->GetWindowName(), extensions);
	window->InitiWindowSurface(instance->GetVkInstance(), instance->GetVkSurface());
	device = new Device(instance);
	swapChain = new SwapChain(instance, device, window);
	pipeline = new Pipeline(device, swapChain, "Rendering/Shaders/default.vert.spv", "Rendering/Shaders/default.frag.spv");
	commandBuffer = new CommandBuffer(device, swapChain, pipeline, maxFramesInFlight);
}

Renderer::~Renderer() {
	delete commandBuffer;
	delete pipeline;
	delete swapChain;
	delete device;
	delete instance;
}

void Renderer::drawFrame() {
	commandBuffer->PresentCommand();
}

void Renderer::reset() {
	vkDeviceWaitIdle(*device->GetLogicalDevice());
}
