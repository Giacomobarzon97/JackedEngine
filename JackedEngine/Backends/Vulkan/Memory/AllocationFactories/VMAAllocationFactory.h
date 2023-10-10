#pragma once
#include "Backends/Vulkan/Device.h"
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Backends/Vulkan/Memory/Allocations/IndexBufferAllocations/VMAIndexBufferAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/VertexBufferAllocations/VMAVertexBufferAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/UniformAllocations/VMAUniformAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/ImageAllocations/VMAImageAllocation.h"

class VMAAllocationFactory : public BaseAllocationFactory {
public:
	VMAAllocationFactory(const Device& device);
	VMAAllocationFactory(VMAAllocationFactory&) = delete;
	virtual ~VMAAllocationFactory() override;

	VMAAllocationFactory& operator=(VMAAllocationFactory&) = delete;

	virtual const VMAIndexBufferAllocation* CreateIndexBufferAllocation(const void* data, const uint32_t dataSize) const override;
	virtual const VMAVertexBufferAllocation* CreateVertexBufferAllocation(const void* data, const uint32_t dataSize) const override;
	virtual const VMAUniformAllocation* CreateUniformAllocation(const uint32_t dataSize) const override;
	virtual const VMAImageAllocation* CreateImageAllocation(const std::vector<const void*> data, const int width, const int height, VkImageViewType imageViewType, VkImageCreateFlags flags) const override;

private:
	VMAAllocator allocator;
};