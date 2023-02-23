#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/UBODescriptorPool.h"
#include "Rendering/Buffers/UniformBuffer.h"
#include "Rendering/Buffers/ImageBuffer.h"

class UBODescriptorSet : public BaseDescriptorSet{
public:
	UBODescriptorSet(const Device& device, const UBODescriptorPool& descriptorPool);
	UBODescriptorSet(UBODescriptorSet&) = delete;
	virtual ~UBODescriptorSet() override;

	UBODescriptorSet&operator=(UBODescriptorSet&) = delete;

	virtual void UpdateDescriptorSet(const glm::mat4 mvpMatrix) const;

private:
	struct UniformBufferObject {
		glm::mat4 mvp;
	};
	const UniformBuffer mvpUniform;

};