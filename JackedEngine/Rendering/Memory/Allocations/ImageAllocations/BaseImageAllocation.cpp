#include "BaseImageAllocation.h"

BaseImageAllocation::~BaseImageAllocation() {}

const VkImageView& BaseImageAllocation::GetImageView() const{
	return imageView;
}
