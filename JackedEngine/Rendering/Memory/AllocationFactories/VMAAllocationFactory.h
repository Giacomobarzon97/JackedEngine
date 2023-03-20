#pragma once
#include "Rendering/Device.h"
#include "Rendering/Memory/AllocationFactories/BaseAllocationFactory.h"
#include "Rendering/Memory/BufferAllocations/VertexBufferAllocations/VMAVertexBufferAllocation.h"
#include "Rendering/Memory/BufferAllocations/IndexBufferAllocations/VMAIndexBufferAllocation.h"
#include "Rendering/Memory/BufferAllocations/UniformBufferAllocations/VMAUniformBufferAllocation.h"
#include "Rendering/Memory/BufferAllocations/ImageBufferAllocations/VMAImageBufferAllocation.h"
#include "Rendering/Memory/BufferAllocations/CubemapBufferAllocations/VMACubemapBufferAllocation.h"

class VMAAllocationFactory : public BaseAllocationFactory {
public:
	VMAAllocationFactory(const Device& device);
	VMAAllocationFactory(VMAAllocationFactory&) = delete;
	virtual ~VMAAllocationFactory() override;

	VMAAllocationFactory& operator=(VMAAllocationFactory&) = delete;

	virtual const VMAVertexBufferAllocation* CreateVertexBufferAllocation(const void* data, const size_t dataSize) const override;
	virtual const VMAIndexBufferAllocation* CreateIndexBufferAllocation(const void* data, const size_t dataSize) const override;
	virtual const VMAUniformBufferAllocation* CreateUniformBufferAllocation(const size_t dataSize) const override;
	virtual const VMAImageBufferAllocation* CreateImageBufferAllocation(const void* data, const int width, const int height) const override;
	virtual const VMACubemapBufferAllocation* CreateCubemapBufferAllocation(const void* frontFaceData, const void* backFaceData, const void* upFaceData, const void* downFaceData, const void* rightFaceData, const void* leftFaceData, const int width, const int height) const override;

private:
	VMAAllocator allocator;
};