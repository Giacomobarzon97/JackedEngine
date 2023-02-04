#pragma once

#include <string>
#include "Windows/BaseWindow.h"
#include "Rendering/Device.h"
#include "Rendering/Pipeline.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/CommandBuffer.h"

class Renderer {
public:
	Renderer(const BaseWindow* const window, const int maxFramesInFlight);
	Renderer(Renderer &) = delete;
	~Renderer();
	Renderer &operator=(Renderer &) = delete;

	void DrawFrame();
	void Reset() const;

	static void FramebufferResizeCallback(void * buffer);

private:
	Device* device;
	const Pipeline* pipeline;
	const VertexBuffer* vertexBuffer;
	std::vector<const CommandBuffer*> commandBuffers;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
	int maxFramesInFlight;
};
