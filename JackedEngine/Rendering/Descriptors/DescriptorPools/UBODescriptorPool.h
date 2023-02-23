#pragma once
#include <array>
#include "Rendering/Descriptors/DescriptorPools/BaseDescriptorPool.h"
#include "Rendering/Buffers/UniformBuffer.h"

class UBODescriptorPool : public BaseDescriptorPool{
public:
	UBODescriptorPool(const Device& device, int maxSets);
	UBODescriptorPool(UBODescriptorPool&) = delete;
	virtual ~UBODescriptorPool() override;

	UBODescriptorPool&operator=(UBODescriptorPool&) = delete;

};