#include "Renderer.h"

Renderer::Renderer(std::string appName, BaseWindow* window) {

	uint32_t windowExtensionCount = 0;
	const char** windowExtensions = window->GetRequiredExtensions(&windowExtensionCount);
	std::vector<const char*> extensions(windowExtensions, windowExtensions + windowExtensionCount);

	instance = new Instance(appName, extensions);
	windowSurface = new WindowSurface(instance, window);
	window->InitiWindowSurface(instance, windowSurface->getVkSurface());
	device = new Device(instance, windowSurface);
}

Renderer::~Renderer() {
	delete device;
	delete windowSurface;
	delete instance;
}