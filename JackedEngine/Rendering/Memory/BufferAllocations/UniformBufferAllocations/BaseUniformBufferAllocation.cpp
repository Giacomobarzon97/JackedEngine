#include "BaseUniformBufferAllocation.h"

BaseUniformBufferAllocation::~BaseUniformBufferAllocation() {}

const VkBuffer& BaseUniformBufferAllocation::GetBuffer() const {
	return buffer;
}