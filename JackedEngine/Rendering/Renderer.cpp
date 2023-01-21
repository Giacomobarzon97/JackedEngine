#include "Renderer.h"

Renderer::Renderer(std::string appName, const char** windowExtensions, uint32_t windowExtensionsCount, GLFWwindow* window) {
	std::vector<const char*> extensions(windowExtensions, windowExtensions + windowExtensionsCount);
	instance = new Instance(appName, extensions);
	windowSurface = new GLFWWindowSurface(instance->GetVkInstance(), window);
	device = new Device(instance->GetVkInstance(), windowSurface->getVkSurface());
}

Renderer::~Renderer() {
	delete device;
	delete windowSurface;
	delete instance;
}