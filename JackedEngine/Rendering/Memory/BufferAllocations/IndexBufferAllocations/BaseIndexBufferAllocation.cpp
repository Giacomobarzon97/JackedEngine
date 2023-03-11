#include "BaseIndexBufferAllocation.h"


BaseIndexBufferAllocation::~BaseIndexBufferAllocation() {}

const VkBuffer BaseIndexBufferAllocation::GetBuffer() const {
	return buffer;
}