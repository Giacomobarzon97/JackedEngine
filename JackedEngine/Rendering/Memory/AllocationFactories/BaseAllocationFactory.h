#pragma once
#include "Rendering/Memory/BufferAllocations/BaseBufferAllocation.h"

class BaseAllocationFactory {
public:
	virtual const BaseBufferAllocation* CreateBufferAllocation(const void* data, const size_t dataSize) const = 0;
};