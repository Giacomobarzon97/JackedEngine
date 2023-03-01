#pragma once
#include <vulkan/vulkan.h>
#include<vector>
#include "Rendering/Buffers/BaseBuffer.h"
#include "Rendering/Device.h"
#include "Rendering/Data/Model.h"

class VertexBuffer : public BaseBuffer{
public:
	VertexBuffer(const Device& device, const std::string objFilePath);
	VertexBuffer(VertexBuffer&) = delete;
	virtual ~VertexBuffer() override;

	VertexBuffer &operator=(VertexBuffer &) = delete;

	const VkBuffer& GetVertexBuffer() const;
	const VkBuffer& GetIndexBuffer() const;
	const uint32_t GetIndicesNumber() const;

private:
	uint32_t nVertices;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
};