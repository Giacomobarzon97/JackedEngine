#pragma once
#include "Backends/Vulkan/Device.h"
#include "Backends/Vulkan/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Backends/Vulkan/Memory/Allocations/IndexBufferAllocations/VMAIndexBufferAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/VertexBufferAllocations/VMAVertexBufferAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/UniformAllocations/VMAUniformAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/Image2DAllocations/VMAImage2DAllocation.h"
#include "Backends/Vulkan/Memory/Allocations/CubemapAllocations/VMACubemapAllocation.h"

class VMAAllocationFactory : public BaseAllocationFactory {
public:
	VMAAllocationFactory(const Device& device);
	VMAAllocationFactory(VMAAllocationFactory&) = delete;
	virtual ~VMAAllocationFactory() override;

	VMAAllocationFactory& operator=(VMAAllocationFactory&) = delete;

	virtual const VMAIndexBufferAllocation* CreateIndexBufferAllocation(const void* data, const uint32_t dataSize) const override;
	virtual const VMAVertexBufferAllocation* CreateVertexBufferAllocation(const void* data, const uint32_t dataSize) const override;
	virtual const VMAUniformAllocation* CreateUniformAllocation(const uint32_t dataSize) const override;
	virtual const VMAImage2DAllocation* CreateImage2DAllocation(const void* data, const int width, const int height) const override;
	virtual const VMACubemapAllocation* CreateCubemapAllocation(const std::array<const void*, 6> data, const int width, const int height) const override;

private:
	VMAAllocator allocator;
};