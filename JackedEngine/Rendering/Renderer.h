#pragma once

#include <string>
#include "Windows/BaseWindow.h"
#include "Rendering/Device.h"
#include "Rendering/Pipeline.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/CommandBuffer.h"

class Renderer {
public:
	Renderer(BaseWindow* window, int maxFramesInFlight);
	Renderer(Renderer &) = delete;
	~Renderer();
	Renderer &operator=(Renderer &) = delete;

	void DrawFrame();
	void Reset();

	static void FramebufferResizeCallback(void * buffer);

private:
	Device* device;
	Pipeline* pipeline;
	VertexBuffer* vertexBuffer;
	std::vector<CommandBuffer*> commandBuffers;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
	int maxFramesInFlight;
};
