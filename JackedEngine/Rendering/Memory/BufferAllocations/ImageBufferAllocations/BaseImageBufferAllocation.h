#pragma once
#include "Rendering/Memory/BufferAllocations/BaseBufferAllocation.h"

class BaseImageBufferAllocation : public BaseBufferAllocation {
public:
	const VkImageView& GetImageView() const;

protected:
	VkImage image;
	VkImageView imageView;
};