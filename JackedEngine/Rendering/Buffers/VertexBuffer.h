#pragma once
#include <vulkan/vulkan.h>
#include<vector>
#include "Rendering/Buffers/BaseBuffer.h"
#include "Rendering/Device.h"
#include "Logic/Model.h"

class VertexBuffer : public BaseBuffer{
public:
	VertexBuffer(const Device& device, const Model& model);
	VertexBuffer(VertexBuffer&) = delete;
	virtual ~VertexBuffer() override;

	VertexBuffer &operator=(VertexBuffer &) = delete;

	const VkBuffer& GetVertexBuffer() const;
	const VkBuffer& GetIndexBuffer() const;
	const uint32_t GetIndicesNumber() const;

private:
	const Model& model;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
};