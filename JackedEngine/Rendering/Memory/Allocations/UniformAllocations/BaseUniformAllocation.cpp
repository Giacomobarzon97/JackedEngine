#include "BaseUniformAllocation.h"

BaseUniformAllocation::~BaseUniformAllocation() {}

const VkBuffer& BaseUniformAllocation::GetBuffer() const {
	return buffer;
}