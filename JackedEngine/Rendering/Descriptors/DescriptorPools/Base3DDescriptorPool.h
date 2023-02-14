#pragma once
#include "Rendering/Descriptors/DescriptorPools/BaseDescriptorPool.h"
#include "Rendering/Buffers/UniformBuffer.h"

class Base3DDescriptorPool : public BaseDescriptorPool{
public:
	Base3DDescriptorPool(const Device* const device, int nFrames);
	Base3DDescriptorPool(Base3DDescriptorPool &) = delete;
	virtual ~Base3DDescriptorPool() override;

	Base3DDescriptorPool &operator=(Base3DDescriptorPool &) = delete;

};