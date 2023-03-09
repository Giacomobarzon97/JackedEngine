#include "BaseBufferAllocation.h"

BaseBufferAllocation::~BaseBufferAllocation() {}

const VkBuffer BaseBufferAllocation::GetBuffer() const {
	return buffer;
}