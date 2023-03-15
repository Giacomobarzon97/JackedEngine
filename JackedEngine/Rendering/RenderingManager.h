#pragma once
#include <unordered_map>
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Rendering/Resources/GPUResources/GPUModel.h"
#include "Rendering/Descriptors/DescriptorSets/ObjectDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorSets/FrameDescriptorSet.h"

class RenderingManager {
public:
	RenderingManager(const Device& device, const BaseAllocationFactory& allocationFactory, const unsigned int nFrames);
	RenderingManager(RenderingManager&) = delete;
	~RenderingManager();

	RenderingManager& operator=(RenderingManager&) = delete;

	const GPUModel& CreateOrGetModel(const std::string modelPath);
	const ObjectDescriptorSet& CreateOrGetObjectDescriptor(const std::string objectId, const std::string imagePath, const unsigned int frameNumber);
	const FrameDescriptorSet& GetFrameDescriptor(const unsigned int frameNumber) const;

	const FrameDescriptorLayout& GetFrameDescriptorLayout() const;
	const ObjectDescriptorLayout& GetObjectDescriptorLayout() const;

private:
	const Device& device;
	const BaseAllocationFactory& allocationFactory;
	const unsigned int nFrames;

	ObjectDescriptorLayout objectDescriptorLayout;
	FrameDescriptorLayout frameDescriptorLayout;
	FrameDescriptorPool frameDescriptorPool;
	std::vector<const FrameDescriptorSet*> frameDescriptorSets;

	std::unordered_map <std::string, const GPUModel*> modelMap;
	std::unordered_map <std::string, const GPUImage*> imageMap;
	std::unordered_map <std::string, const ObjectDescriptorPool*> objectDescriptorPoolMap;
	std::unordered_map <std::string, std::vector<const ObjectDescriptorSet*>> objectDescriptorSetsMap;
};