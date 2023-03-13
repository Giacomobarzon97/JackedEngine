#pragma once
#include "Rendering/Descriptors/DescriptorPools/BaseDescriptorPool.h"

class ObjectDescriptorPool : public BaseDescriptorPool{
public:
	ObjectDescriptorPool(const Device& device, int maxSets);
	ObjectDescriptorPool(ObjectDescriptorPool&) = delete;
	virtual ~ObjectDescriptorPool() override;

	ObjectDescriptorPool& operator=(ObjectDescriptorPool&) = delete;
};