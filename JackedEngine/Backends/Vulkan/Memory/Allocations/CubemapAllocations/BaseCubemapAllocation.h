#pragma once
#include <vulkan/vulkan.h>

class BaseCubemapAllocation {
public:
	virtual ~BaseCubemapAllocation() = 0;
	const VkImageView& GetImageView() const;

protected:
	VkImage image;
	VkImageView imageView;
};