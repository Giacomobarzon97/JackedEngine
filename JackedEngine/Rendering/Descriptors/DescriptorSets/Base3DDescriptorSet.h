#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/Base3DDescriptorPool.h"
#include "Rendering/Buffers/UniformBuffer.h"

class Base3DDescriptorSet : public BaseDescriptorSet{
public:
	Base3DDescriptorSet(const Device* const device, const Base3DDescriptorPool* const);
	Base3DDescriptorSet(Base3DDescriptorSet&) = delete;
	virtual ~Base3DDescriptorSet() override;

	Base3DDescriptorSet &operator=(Base3DDescriptorSet &) = delete;

	void UpdateDescriptorSet() const;

private:
	const UniformBuffer* const mvpUniform;

};