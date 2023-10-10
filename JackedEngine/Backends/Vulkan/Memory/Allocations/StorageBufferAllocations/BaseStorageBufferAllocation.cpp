#include "BaseStorageBufferAllocation.h"

BaseStorageBufferAllocation::BaseStorageBufferAllocation(const uint32_t elementSize, const uint32_t nElements) : 
	elementSize(elementSize),
	nElements(nElements)
{

}

BaseStorageBufferAllocation::~BaseStorageBufferAllocation() {}

const VkBuffer& BaseStorageBufferAllocation::GetBuffer() const {
	return buffer;
}