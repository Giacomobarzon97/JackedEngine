#pragma once

#include <string>
#include "Rendering/Device.h"
#include "Rendering/Instance.h"
#include "Windows/BaseWindow.h"
#include "Rendering/SwapChain.h"
#include "Rendering/Pipeline.h"
#include "Rendering/CommandBuffer.h"

class Renderer {
public:
	Renderer(BaseWindow* window, int maxFramesInFlight);
	Renderer(Renderer &) = delete;
	~Renderer();
	Renderer &operator=(Renderer &) = delete;

	void DrawFrame();
	void Reset();

private:
	Instance* instance;
	Device* device;
	SwapChain* swapChain;
	Pipeline* pipeline;
	CommandBuffer* commandBuffer;
};
