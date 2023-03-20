#pragma once
#include <vulkan/vulkan.h>

class BaseCubemapBufferAllocation {
public:
	virtual ~BaseCubemapBufferAllocation() = 0;
	const VkImageView& GetImageView() const;

protected:
	VkImage image;
	VkImageView imageView;
};