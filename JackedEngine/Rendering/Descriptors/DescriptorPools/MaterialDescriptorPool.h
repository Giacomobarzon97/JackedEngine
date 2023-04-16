#pragma once
#include "Rendering/Descriptors/DescriptorPools/BaseDescriptorPool.h"

class MaterialDescriptorPool : public BaseDescriptorPool{
public:
	MaterialDescriptorPool(const Device& device, int maxSets);
	MaterialDescriptorPool(MaterialDescriptorPool&) = delete;
	virtual ~MaterialDescriptorPool() override;

	MaterialDescriptorPool& operator=(MaterialDescriptorPool&) = delete;
};