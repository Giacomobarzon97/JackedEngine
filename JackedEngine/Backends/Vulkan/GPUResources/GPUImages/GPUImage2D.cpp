#include "GPUImage2D.h"

GPUImage2D::GPUImage2D(const BaseAllocationFactory& allocationFactory, const CPUImage2D& image) {
	imageBufferAllocation = allocationFactory.CreateImage2DAllocation(
		image.GetPixelData(),
		image.GetWidth(),
		image.GetHeight()
	);
}

GPUImage2D::~GPUImage2D() {
	delete imageBufferAllocation;
}

const VkImageView& GPUImage2D::GetImageView() const {
	return imageBufferAllocation->GetImageView();
}
