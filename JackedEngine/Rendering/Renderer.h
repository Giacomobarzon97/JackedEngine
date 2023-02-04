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

private:
	Device* device;
	Pipeline* pipeline;
	VertexBuffer* vertexBuffer;
	CommandBuffer* commandBuffer;
};
