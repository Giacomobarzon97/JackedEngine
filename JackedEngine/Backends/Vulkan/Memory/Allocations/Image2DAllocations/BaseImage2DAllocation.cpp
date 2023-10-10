#include "BaseImage2DAllocation.h"

BaseImage2DAllocation::~BaseImage2DAllocation() {}

const VkImageView& BaseImage2DAllocation::GetImageView() const{
	return imageView;
}
