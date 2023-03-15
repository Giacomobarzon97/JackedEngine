#pragma once

#include <string>
#include "Scene/SceneObjects/Cameras/BaseCameraObject.h"
#include "Scene/SceneObjects/RenderableObject.h"
#include "Windows/BaseWindow.h"
#include "Rendering/Device.h"
#include "Rendering/Pipelines/Base3DPipeline.h"
#include "Rendering/CommandBuffers/Graphical3DCommandBuffer.h"
#include "Rendering/Memory/AllocationFactories/VMAAllocationFactory.h"
#include "Rendering/RenderingManager.h"
#include "Rendering/Samplers/LinearRepeatSampler.h"

class Renderer {
public:
	Renderer(const BaseWindow& window, const BaseCameraObject& camera);
	Renderer(Renderer &) = delete;
	~Renderer();

	Renderer &operator=(Renderer &) = delete;

	void DrawObject(std::vector<RenderableObject> objects);
	void Reset() const;

	static void FramebufferResizeCallback(void * buffer);

private:
	int maxFramesInFlight = 2;

	const BaseCameraObject& camera;
	Device device;
	VMAAllocationFactory allocationFactory;
	LinearRepeatSampler sampler;
	RenderingManager renderingManager;
	const Base3DPipeline pipeline;
	std::vector<Graphical3DCommandBuffer* > commandBuffers;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
};
