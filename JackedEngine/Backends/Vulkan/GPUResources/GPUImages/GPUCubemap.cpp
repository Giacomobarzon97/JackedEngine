#include "GPUCubemap.h"

GPUCubemap::GPUCubemap(const BaseAllocationFactory& allocationFactory, const CPUCubemap& image) {
	imageBufferAllocation = allocationFactory.CreateCubemapAllocation(
		image.GetPixelData(),
		image.GetWidth(),
		image.GetHeight()
	);
}

GPUCubemap::~GPUCubemap() {
	delete imageBufferAllocation;
}

const VkImageView& GPUCubemap::GetImageView() const {
	return imageBufferAllocation->GetImageView();
}
