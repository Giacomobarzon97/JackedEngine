#pragma once

#include <string>
#include "Rendering/Device.h"
#include "Rendering/Instance.h"
#include "Windows/BaseWindow.h"
#include "Rendering/WindowSurface.h"

class Renderer {
public:
	Renderer(std::string appName, BaseWindow* window);
	Renderer(const Renderer &) = delete;
	Renderer(Renderer &) = delete;
	~Renderer();

	Renderer &operator=(const Renderer &) = delete;
	Renderer &operator=(Renderer &) = delete;

private:
	Instance* instance;
	Device* device;
	WindowSurface* windowSurface;
};
