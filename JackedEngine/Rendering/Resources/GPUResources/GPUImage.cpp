#include "GPUImage.h"

GPUImage::GPUImage(const BaseAllocationFactory& allocationFactory, const CPUImage& image) {
	imageBufferAllocation = allocationFactory.CreateImageBufferAllocation(
		image.GetPixelData(),
		image.GetWidth(),
		image.GetHeight()
	);
}

GPUImage::~GPUImage() {
	delete imageBufferAllocation;
}

const VkImageView& GPUImage::GetImageView() const {
	return imageBufferAllocation->GetImageView();
}
