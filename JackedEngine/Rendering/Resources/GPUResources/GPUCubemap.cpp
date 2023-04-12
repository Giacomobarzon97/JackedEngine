#include "GPUCubemap.h"

GPUCubemap::GPUCubemap(const BaseAllocationFactory& allocationFactory, const CPUImage& frontFaceData, const CPUImage& backFaceData, const CPUImage& upFaceData, const CPUImage& downFaceData, const CPUImage& rightFaceData, const CPUImage& leftFaceData) {
	std::vector<const void*> data(6);
	data[0] = frontFaceData.GetPixelData();
	data[1] = backFaceData.GetPixelData();
	data[2] = upFaceData.GetPixelData();
	data[3] = downFaceData.GetPixelData();
	data[4] = rightFaceData.GetPixelData();
	data[5] = leftFaceData.GetPixelData();

	cubemapBuffer = allocationFactory.CreateImageAllocation(
		data,
		frontFaceData.GetWidth(),
		frontFaceData.GetHeight(),
		VK_IMAGE_VIEW_TYPE_CUBE,
		VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT
	);
}

GPUCubemap::~GPUCubemap() {
	delete cubemapBuffer;
}

const VkImageView& GPUCubemap::GetImageView() const {
	return cubemapBuffer->GetImageView();
}