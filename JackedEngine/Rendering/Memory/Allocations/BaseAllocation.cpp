#include "BaseAllocation.h"

BaseAllocation::~BaseAllocation(){}

const VkBuffer BaseAllocation::GetBuffer() const {
	return buffer;
}