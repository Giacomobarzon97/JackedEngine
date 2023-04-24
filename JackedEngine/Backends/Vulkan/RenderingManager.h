#pragma once
#include <unordered_map>
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Rendering/Resources/GPUResources/GPUModel.h"
#include "Rendering/Resources/CPUResources/CPUModels/CPUGenericMesh.h"
#include "Rendering/Descriptors/DescriptorSets/MaterialDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorSets/FrameDescriptorSet.h"

class RenderingManager {
public:
	RenderingManager(const Device& device, const BaseAllocationFactory& allocationFactory, const BaseSampler& sampler, const unsigned int nFrames);
	RenderingManager(RenderingManager&) = delete;
	~RenderingManager();

	RenderingManager& operator=(RenderingManager&) = delete;

	const GPUModel& CreateOrGetModel(const std::string modelPath);
	const MaterialDescriptorSet& CreateOrGetObjectDescriptor(const std::string objectId, const std::string imagePath, const unsigned int frameNumber);
	const FrameDescriptorSet& GetFrameDescriptor(const unsigned int frameNumber) const;

	const FrameDescriptorLayout& GetFrameDescriptorLayout() const;
	const MaterialDescriptorLayout& GetObjectDescriptorLayout() const;

private:
	const Device& device;
	const BaseAllocationFactory& allocationFactory;
	const BaseSampler& sampler;
	const unsigned int nFrames;

	MaterialDescriptorLayout objectDescriptorLayout;
	FrameDescriptorLayout frameDescriptorLayout;
	FrameDescriptorPool frameDescriptorPool;
	std::vector<const FrameDescriptorSet*> frameDescriptorSets;

	std::unordered_map <std::string, const GPUModel*> modelMap;
	std::unordered_map <std::string, const GPUImage*> imageMap;
	std::unordered_map <std::string, const MaterialDescriptorPool*> objectDescriptorPoolMap;
	std::unordered_map <std::string, std::vector<const MaterialDescriptorSet*>> objectDescriptorSetsMap;
};