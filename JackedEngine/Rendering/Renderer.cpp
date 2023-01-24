#include "Renderer.h"

Renderer::Renderer(BaseWindow* window) {
	uint32_t windowExtensionCount = 0;
	const char** windowExtensions = window->GetRequiredExtensions(&windowExtensionCount);
	std::vector<const char*> extensions(windowExtensions, windowExtensions + windowExtensionCount);

	instance = new Instance(window->GetWindowName(), extensions);
	window->InitiWindowSurface(instance->GetVkInstance(), instance->GetVkSurface());
	device = new Device(instance);
	swapChain = new SwapChain(instance, device, window);
	pipeline = new Pipeline(device, swapChain, "Rendering/Shaders/default.vert.spv", "Rendering/Shaders/default.frag.spv");
}

Renderer::~Renderer() {
	delete pipeline;
	delete swapChain;
	delete device;
	delete instance;
}