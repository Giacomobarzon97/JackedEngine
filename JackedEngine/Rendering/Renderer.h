#pragma once

#include <string>
#include "Rendering/Device.h"
#include "Rendering/Instance.h"
#include "Windows/BaseWindow.h"
#include "Rendering/WindowSurface.h"
#include "Rendering/SwapChain.h"

class Renderer {
public:
	Renderer(BaseWindow* window);
	Renderer(Renderer &) = delete;
	~Renderer();
	Renderer &operator=(Renderer &) = delete;

private:
	Instance* instance;
	Device* device;
	WindowSurface* windowSurface;
	SwapChain* swapChain;
};
