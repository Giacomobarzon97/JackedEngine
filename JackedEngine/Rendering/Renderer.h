#pragma once

#include <string>
#include "Scene/SceneObjects/Cameras/BaseCameraObject.h"
#include "Scene/SceneObjects/RenderableObject.h"
#include "Windows/BaseWindow.h"
#include "Rendering/Device.h"
#include "Rendering/Pipelines/Object3DPipeline.h"
#include "Rendering/CommandBuffers/GraphicalCommandBuffer.h"
#include "Rendering/Memory/AllocationFactories/VMAAllocationFactory.h"
#include "Rendering/RenderingManager.h"
#include "Rendering/Samplers/LinearRepeatSampler.h"

#include "Rendering/Pipelines/SkyboxPipeline.h"

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
	const Object3DPipeline object3DPipeline;
	std::vector<GraphicalCommandBuffer* > commandBuffers;

	GPUCubemap cubemap;
	SkyboxDescriptorPool skyboxDescriptorPool;
	SkyboxDescriptorLayout skyboxDescriptorLayout;
	SkyboxDescriptorSet skyboxDescriptorSet;
	SkyboxPipeline skyboxPipeline;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
};
