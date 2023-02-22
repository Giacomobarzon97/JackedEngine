#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/Base3DDescriptorPool.h"
#include "Rendering/Buffers/UniformBuffer.h"
#include "Rendering/Buffers/ImageBuffer.h"

class Base3DDescriptorSet : public BaseDescriptorSet{
public:
	Base3DDescriptorSet(const Device& device, const Base3DDescriptorPool& descriptorPool, const ImageBuffer& imageBuffer);
	Base3DDescriptorSet(Base3DDescriptorSet&) = delete;
	virtual ~Base3DDescriptorSet() override;

	Base3DDescriptorSet &operator=(Base3DDescriptorSet &) = delete;

	virtual void UpdateDescriptorSet(const BaseCameraObject& camera, const RenderableObject& object) const override;

private:
	struct UniformBufferObject {
		glm::mat4 mvp;
	};
	const UniformBuffer mvpUniform;

};