#pragma once

#include <Windows.h>
#include <string>
#include "Device.h"
#include "Instance.h"
#include "WindowSurfaces/GLFWWindowSurface.h"
#include <GLFW/glfw3.h>

class Renderer {
public:
	Renderer(std::string appName, const char** windowExtensions, uint32_t windowExtensionsCount, GLFWwindow* window);
	~Renderer();

	Renderer(const Renderer &) = delete;
	Renderer &operator=(const Renderer &) = delete;

private:
	Instance* instance;
	Device* device;
	BaseWindowSurface* windowSurface;
};
