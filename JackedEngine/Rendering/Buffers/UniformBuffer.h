#pragma once
#include "Rendering/Buffers/BaseBuffer.h"
#include "Rendering/Descriptors/DescriptorPools/BaseDescriptorPool.h"

class UniformBuffer : public BaseBuffer{
public:
	UniformBuffer(const Device& device, const size_t bufferSize);
	UniformBuffer(UniformBuffer&) = delete;
	virtual ~UniformBuffer() override;

	UniformBuffer &operator=(UniformBuffer &) = delete;

	void UpdateUniformBuffer(const void * data) const;
	const VkBuffer& GetUniformBuffer() const;

private:
	VkBuffer uniformBuffer;
	VkDeviceMemory uniformBufferMemory;
	void* uniformBufferMapped;
	const size_t bufferSize;
};