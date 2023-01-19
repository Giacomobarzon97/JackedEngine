#include "Renderer.h"

Renderer::Renderer(std::string appName, const char** windowExtensions, uint32_t windowExtensionsCount, GLFWwindow* window) {
	std::vector<const char*> extensions(windowExtensions, windowExtensions + windowExtensionsCount);
	instance = new Instance(appName, extensions);
	queue = new Queue(instance->GetVkInstance());
	windowSurface = new GLFWWindowSurface(instance->GetVkInstance(), window);
}

Renderer::~Renderer() {
	delete queue;
	delete windowSurface;
	delete instance;
}