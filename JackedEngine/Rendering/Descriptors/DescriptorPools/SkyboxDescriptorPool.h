#pragma once
#include "Rendering/Descriptors/DescriptorPools/BaseDescriptorPool.h"

class SkyboxDescriptorPool : public BaseDescriptorPool {
public:
	SkyboxDescriptorPool(const Device& device, int maxSets);
	SkyboxDescriptorPool(SkyboxDescriptorPool&) = delete;
	virtual ~SkyboxDescriptorPool() override;

	SkyboxDescriptorPool& operator=(SkyboxDescriptorPool&) = delete;
};