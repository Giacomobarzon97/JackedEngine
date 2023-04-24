#include "GPUImage.h"

GPUImage::GPUImage(const BaseAllocationFactory& allocationFactory, const CPUImage& image) {

	VkImageViewType imageViewType;
	VkImageCreateFlags flags;

	switch (image.GetImageType()) {
	case IMAGE_2D:
		imageViewType = VK_IMAGE_VIEW_TYPE_2D;
		flags = 0;
		break;
	case CUBEMAP:
		imageViewType = VK_IMAGE_VIEW_TYPE_CUBE;
		flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
		break;
	default:
		throw std::runtime_error("Image type not supported");
	}

	imageBufferAllocation = allocationFactory.CreateImageAllocation(
		image.GetPixelData(),
		image.GetWidth(),
		image.GetHeight(),
		imageViewType,
		flags
	);
}

GPUImage::~GPUImage() {
	delete imageBufferAllocation;
}

const VkImageView& GPUImage::GetImageView() const {
	return imageBufferAllocation->GetImageView();
}
