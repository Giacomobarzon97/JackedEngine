#pragma once
#include "Rendering/Memory/BufferAllocations/BaseBufferAllocation.h"

class BaseUniformBufferAllocation : public BaseBufferAllocation{
public:
	virtual void UpdateBuffer(const void* data) const = 0;
};