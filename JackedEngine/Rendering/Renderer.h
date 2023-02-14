#pragma once

#include <string>
#include "Windows/BaseWindow.h"
#include "Rendering/Device.h"
#include "Rendering/Pipeline.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/CommandBuffer.h"
#include "Rendering/Descriptors/DescriptorPools/Base3DDescriptorPool.h"
#include "Rendering/Descriptors/DescriptorSets/Base3DDescriptorSet.h"

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
	const Base3DDescriptorPool* descriptorPool;
	std::vector<const Base3DDescriptorSet*> descriptorSets;
 
	bool framebufferResized = false;
	uint32_t currentFrame = 0;
	int maxFramesInFlight;
};
