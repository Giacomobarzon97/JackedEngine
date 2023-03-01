#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/ImageDescriptorPool.h"
#include "Rendering/Buffers/ImageBuffer.h"

class ImageDescriptorSet : public BaseDescriptorSet{
public:
	ImageDescriptorSet(const Device& device, const ImageDescriptorPool& descriptorPool, std::string imagePath );
	ImageDescriptorSet(ImageDescriptorSet&) = delete;
	virtual ~ImageDescriptorSet() override;

	ImageDescriptorSet& operator=(ImageDescriptorSet&) = delete;

private:
	const ImageBuffer imageBuffer;
};