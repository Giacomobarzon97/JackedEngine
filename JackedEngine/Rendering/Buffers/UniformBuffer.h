#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include "Rendering/Buffers/BaseBuffer.h"

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

class UniformBuffer : public BaseBuffer{
public:
	UniformBuffer(const Device* const device);
	UniformBuffer(UniformBuffer&) = delete;
	~UniformBuffer();

	UniformBuffer &operator=(UniformBuffer &) = delete;

	void UpdateUniformBuffer() const;

private:
	static std::chrono::steady_clock::time_point startTime;
	VkBuffer uniformBuffer;
	VkDeviceMemory uniformBufferMemory;
	void* uniformBufferMapped;
};