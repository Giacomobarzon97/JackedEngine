#include "BaseVertexBufferAllocation.h"

BaseVertexBufferAllocation::~BaseVertexBufferAllocation() {}

const VkBuffer& BaseVertexBufferAllocation::GetBuffer() const {
	return buffer;
}