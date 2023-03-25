#pragma once
#include "Rendering/Resources/GPUResources/GPUBaseModel.h"

class GPUTexturedModel : public GPUBaseModel {
public:
	GPUTexturedModel(const BaseAllocationFactory& allocationFactory, const CPUModel& model);
	GPUTexturedModel(GPUTexturedModel&) = delete;
	~GPUTexturedModel();

	GPUTexturedModel& operator=(GPUTexturedModel&) = delete;

	const BaseVertexBufferAllocation& GetTextureBufferAllocation() const;

private:
	const BaseVertexBufferAllocation* texCoordsBufferAllocation;
};