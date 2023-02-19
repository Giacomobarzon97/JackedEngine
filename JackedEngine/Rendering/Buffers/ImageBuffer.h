#pragma once
#include "Rendering/Buffers/BaseBuffer.h"

class ImageBuffer : public BaseBuffer {
public:
	ImageBuffer(const Device& device, const char* filePath);
	ImageBuffer(ImageBuffer&) = delete;
	virtual ~ImageBuffer() override;

	ImageBuffer &operator=(ImageBuffer &) = delete;
private:
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;

	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

};