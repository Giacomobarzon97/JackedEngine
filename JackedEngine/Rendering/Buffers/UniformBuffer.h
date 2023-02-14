#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include "Rendering/Buffers/BaseBuffer.h"
#include "Rendering/Descriptors/DescriptorPools/BaseDescriptorPool.h"

struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};

class UniformBuffer : public BaseBuffer{
public:
	UniformBuffer(const Device* const device);
	UniformBuffer(UniformBuffer&) = delete;
	virtual ~UniformBuffer() override;

	UniformBuffer &operator=(UniformBuffer &) = delete;

	void UpdateUniformBuffer() const;
	const VkBuffer* const GetUniformBuffer() const;

private:
	static std::chrono::steady_clock::time_point startTime;
	VkBuffer uniformBuffer;
	VkDeviceMemory uniformBufferMemory;
	void* uniformBufferMapped;
};