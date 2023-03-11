#include "BaseImageBufferAllocation.h"

BaseImageBufferAllocation::~BaseImageBufferAllocation() {}

const VkImageView& BaseImageBufferAllocation::GetImageView() const{
	return imageView;
}
