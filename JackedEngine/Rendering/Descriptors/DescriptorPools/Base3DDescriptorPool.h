#pragma once
#include <array>
#include "Rendering/Descriptors/DescriptorPools/BaseDescriptorPool.h"
#include "Rendering/Buffers/UniformBuffer.h"

class Base3DDescriptorPool : public BaseDescriptorPool{
public:
	Base3DDescriptorPool(const Device& device, int maxSets);
	Base3DDescriptorPool(Base3DDescriptorPool &) = delete;
	virtual ~Base3DDescriptorPool() override;

	Base3DDescriptorPool &operator=(Base3DDescriptorPool &) = delete;

};