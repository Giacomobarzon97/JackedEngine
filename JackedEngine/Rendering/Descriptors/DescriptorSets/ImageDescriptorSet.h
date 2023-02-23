#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/ImageDescriptorPool.h"
#include "Rendering/Buffers/ImageBuffer.h"

class ImageDescriptorSet : public BaseDescriptorSet{
public:
	ImageDescriptorSet(const Device& device, const ImageDescriptorPool& descriptorPool, const char* imagePath );
	ImageDescriptorSet(ImageDescriptorSet&) = delete;
	virtual ~ImageDescriptorSet() override;

	ImageDescriptorSet& operator=(ImageDescriptorSet&) = delete;

private:
	struct UniformBufferObject {
		glm::mat4 mvp;
	};
	const ImageBuffer imageBuffer;
};