#pragma once
#include <vulkan/vulkan.h>

class BaseImage2DAllocation {
public:
	virtual ~BaseImage2DAllocation() = 0;
	const VkImageView& GetImageView() const;

protected:
	VkImage image;
	VkImageView imageView;
};