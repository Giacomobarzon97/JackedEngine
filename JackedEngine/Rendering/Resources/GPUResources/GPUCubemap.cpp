#include "GPUCubemap.h"

GPUCubemap::GPUCubemap(const BaseAllocationFactory& allocationFactory, const CPUImage& frontFaceData, const CPUImage& backFaceData, const CPUImage& upFaceData, const CPUImage& downFaceData, const CPUImage& rightFaceData, const CPUImage& leftFaceData) {
	cubemapBuffer = allocationFactory.CreateCubemapBufferAllocation(
		frontFaceData.GetPixelData(),
		backFaceData.GetPixelData(),
		upFaceData.GetPixelData(),
		downFaceData.GetPixelData(),
		rightFaceData.GetPixelData(),
		leftFaceData.GetPixelData(),
		frontFaceData.GetWidth(),
		frontFaceData.GetHeight()
	);
}

GPUCubemap::~GPUCubemap() {
	delete cubemapBuffer;
}

const VkImageView& GPUCubemap::GetImageView() const {
	return cubemapBuffer->GetImageView();
}