#include "RenderingManager.h"

RenderingManager::RenderingManager(const Device& device, const BaseAllocationFactory& allocationFactory, const BaseSampler& sampler, const unsigned int nFrames) :
	device(device),
	allocationFactory(allocationFactory),
	sampler(sampler),
	nFrames(nFrames),
	objectDescriptorLayout(device),
	frameDescriptorLayout(device),
	frameDescriptorPool(device,nFrames)
{
	frameDescriptorSets.resize(nFrames);
	for (unsigned int i = 0; i < nFrames; i++) {
		frameDescriptorSets[i] = new FrameDescriptorSet(device, frameDescriptorLayout, frameDescriptorPool, allocationFactory);
	}
}

RenderingManager::~RenderingManager() {
	for (unsigned int i = 0; i < nFrames; i++) {
		delete frameDescriptorSets[i];
	}

	for (auto it = modelMap.begin(); it != modelMap.end(); it++) {
		delete it->second;
	}

	for (auto it = imageMap.begin(); it != imageMap.end(); it++) {
		delete it->second;
	}

	for (auto it = objectDescriptorSetsMap.begin(); it != objectDescriptorSetsMap.end(); it++) {
		for (unsigned int i = 0; i < nFrames; i++) {
			delete it->second[i];
		}
	}

	for (auto it = objectDescriptorPoolMap.begin(); it != objectDescriptorPoolMap.end(); it++) {
		delete it->second;
	}
}

const GPUModel& RenderingManager::CreateOrGetModel(const std::string modelPath) {
	CPUGenericMesh mesh = CPUGenericMesh(modelPath, true, true);
	if (modelMap.find(modelPath) == modelMap.end()) {
		mesh.LoadData();
		modelMap[modelPath] = new GPUModel(allocationFactory, mesh);
	} 
	return *modelMap[modelPath];
}

const ObjectDescriptorSet& RenderingManager::CreateOrGetObjectDescriptor(const std::string objectId, const std::string imagePath, const unsigned int frameNumber) {
	if (objectDescriptorPoolMap.find(objectId) == objectDescriptorPoolMap.end()) {
		const GPUImage* image;
		if (imageMap.find(imagePath) == imageMap.end()) {
			image = new GPUImage(allocationFactory, CPUImage(imagePath));
			imageMap[imagePath] = image;
		}
		else {
			image = imageMap[imagePath];
		}

		objectDescriptorPoolMap[objectId] = new ObjectDescriptorPool(device, nFrames);
		objectDescriptorSetsMap[objectId] = std::vector<const ObjectDescriptorSet*>();
		objectDescriptorSetsMap[objectId].resize(nFrames);
		for (unsigned int i = 0; i < nFrames; i++) {
			objectDescriptorSetsMap[objectId][i] = new ObjectDescriptorSet(device, objectDescriptorLayout, *objectDescriptorPoolMap[objectId], allocationFactory, *image, sampler);
		}
	} 
	return *objectDescriptorSetsMap[objectId][frameNumber];
}

const FrameDescriptorSet& RenderingManager::GetFrameDescriptor(const unsigned int frameNumber) const{
	return *frameDescriptorSets[frameNumber];
}


const FrameDescriptorLayout& RenderingManager::GetFrameDescriptorLayout() const {
	return frameDescriptorLayout;
}

const ObjectDescriptorLayout& RenderingManager::GetObjectDescriptorLayout() const {
	return objectDescriptorLayout;
}