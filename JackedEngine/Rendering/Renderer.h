#pragma once

#include <string>
#include "Logic/SceneObjects/Cameras/BaseCameraObject.h"
#include "Windows/BaseWindow.h"
#include "Rendering/Device.h"
#include "Rendering/Pipeline.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/CommandBuffer.h"
#include "Rendering/Descriptors/DescriptorPools/Base3DDescriptorPool.h"
#include "Rendering/Descriptors/DescriptorSets/Base3DDescriptorSet.h"

class Renderer {
public:
	Renderer(const BaseWindow& window, const BaseCameraObject& camera);
	Renderer(Renderer &) = delete;
	~Renderer();

	Renderer &operator=(Renderer &) = delete;

	void DrawFrame();
	void Reset() const;

	static void FramebufferResizeCallback(void * buffer);

private:
	int maxFramesInFlight = 2;

	const BaseCameraObject& camera;
	Device device;
	const Base3DDescriptorPool descriptorPool;
	const Pipeline pipeline;
	const VertexBuffer vertexBuffer;

	std::vector<CommandBuffer* > commandBuffers;
	std::vector<Base3DDescriptorSet* > descriptorSets;
 
	bool framebufferResized = false;
	uint32_t currentFrame = 0;
};
