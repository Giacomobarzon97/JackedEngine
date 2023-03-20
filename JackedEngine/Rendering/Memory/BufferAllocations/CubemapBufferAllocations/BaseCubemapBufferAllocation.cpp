#include "BaseCubemapBufferAllocation.h"

BaseCubemapBufferAllocation::~BaseCubemapBufferAllocation() {}

const VkImageView& BaseCubemapBufferAllocation::GetImageView() const {
	return imageView;
}
