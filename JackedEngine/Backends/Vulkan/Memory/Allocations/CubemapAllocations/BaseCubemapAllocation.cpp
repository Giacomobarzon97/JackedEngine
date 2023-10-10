#include "BaseCubemapAllocation.h"

BaseCubemapAllocation::~BaseCubemapAllocation() {}

const VkImageView& BaseCubemapAllocation::GetImageView() const{
	return imageView;
}
