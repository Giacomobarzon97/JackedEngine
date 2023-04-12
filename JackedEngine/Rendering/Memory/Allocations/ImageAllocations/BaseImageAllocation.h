#pragma once
#include <vulkan/vulkan.h>

class BaseImageAllocation {
public:
	virtual ~BaseImageAllocation() = 0;
	const VkImageView& GetImageView() const;

protected:
	VkImage image;
	VkImageView imageView;
};