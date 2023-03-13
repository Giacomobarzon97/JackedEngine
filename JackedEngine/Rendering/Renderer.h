#pragma once

#include <string>
#include "Logic/SceneObjects/Cameras/BaseCameraObject.h"
#include "Logic/SceneObjects/RenderableObject.h"
#include "Windows/BaseWindow.h"
#include "Rendering/Device.h"
#include "Rendering/Pipelines/Base3DPipeline.h"
#include "Rendering/CommandBuffers/Graphical3DCommandBuffer.h"
#include "Rendering/Descriptors/DescriptorPools/FrameDescriptorPool.h"
#include "Rendering/Descriptors/DescriptorSets/FrameDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/ObjectDescriptorPool.h"
#include "Rendering/Descriptors/DescriptorSets/ObjectDescriptorSet.h"
#include "Rendering/Memory/AllocationFactories/VMAAllocationFactory.h"
#include "Rendering/Resources/GPUResources/GPUModel.h"
#include "Rendering/Resources/GPUResources/GPUImage.h"

class Renderer {
public:
	Renderer(const BaseWindow& window, const BaseCameraObject& camera);
	Renderer(Renderer &) = delete;
	~Renderer();

	Renderer &operator=(Renderer &) = delete;

	void DrawObject(RenderableObject& object);
	void Reset() const;

	static void FramebufferResizeCallback(void * buffer);

private:
	int maxFramesInFlight = 2;

	const BaseCameraObject& camera;
	Device device;
	const FrameDescriptorPool frameDescriptorPool;
	const ObjectDescriptorPool objectDescriptorPool;
	const Base3DPipeline pipeline;

	std::vector<Graphical3DCommandBuffer* > commandBuffers;
	std::vector<FrameDescriptorSet* > frameDescriptorSets;
	std::vector<ObjectDescriptorSet* > objectDescriptorSets;

	VMAAllocationFactory allocationFactory;
	GPUModel model;
	GPUImage image;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
};
