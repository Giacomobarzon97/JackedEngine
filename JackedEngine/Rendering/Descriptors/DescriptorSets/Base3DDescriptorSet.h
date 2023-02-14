#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/Base3DDescriptorPool.h"
#include "Rendering/Buffers/UniformBuffer.h"

class Base3DDescriptorSet : public BaseDescriptorSet{
public:
	Base3DDescriptorSet(const Device& device, const Base3DDescriptorPool& descriptorPool);
	Base3DDescriptorSet(Base3DDescriptorSet&) = delete;
	virtual ~Base3DDescriptorSet() override;

	Base3DDescriptorSet &operator=(Base3DDescriptorSet &) = delete;

	virtual void UpdateDescriptorSet() const override;

private:
	const UniformBuffer mvpUniform;

};