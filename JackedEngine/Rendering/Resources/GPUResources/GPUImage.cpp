#include "GPUImage.h"

GPUImage::GPUImage(const BaseAllocationFactory& allocationFactory, const CPUImage& image) {
	std::vector<const void*> data(1);
	data[0] = image.GetPixelData();

	imageBufferAllocation = allocationFactory.CreateImageAllocation(
		data,
		image.GetWidth(),
		image.GetHeight(),
		VK_IMAGE_VIEW_TYPE_2D,
		0
	);
}

GPUImage::~GPUImage() {
	delete imageBufferAllocation;
}

const VkImageView& GPUImage::GetImageView() const {
	return imageBufferAllocation->GetImageView();
}
