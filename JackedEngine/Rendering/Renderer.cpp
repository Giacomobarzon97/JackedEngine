#include "Renderer.h"

Renderer::Renderer(BaseWindow* window) {
	uint32_t windowExtensionCount = 0;
	const char** windowExtensions = window->GetRequiredExtensions(&windowExtensionCount);
	std::vector<const char*> extensions(windowExtensions, windowExtensions + windowExtensionCount);

	instance = new Instance(window->GetWindowName(), extensions);
	windowSurface = new WindowSurface(instance, window);
	window->InitiWindowSurface(instance->GetVkInstance(), windowSurface->GetVkSurface());
	device = new Device(instance, windowSurface);
	swapChain = new SwapChain(device, window, windowSurface);
}

Renderer::~Renderer() {
	delete swapChain;
	delete device;
	delete windowSurface;
	delete instance;
}