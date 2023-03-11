#pragma once
#include <vulkan/vulkan.h>

class BaseImageBufferAllocation {
public:
	virtual ~BaseImageBufferAllocation() = 0;
	const VkImageView& GetImageView() const;

protected:
	VkImage image;
	VkImageView imageView;
};