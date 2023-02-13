#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include "Rendering/Buffers/BaseBuffer.h"
#include "Rendering/Pipeline.h"

struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};

class UniformBuffer : public BaseBuffer{
public:
	UniformBuffer(const Device* const device, const Pipeline* const pipeline);
	UniformBuffer(UniformBuffer&) = delete;
	~UniformBuffer();

	UniformBuffer &operator=(UniformBuffer &) = delete;

	void UpdateUniformBuffer() const;

	const VkDescriptorSet* const GetDescriptorSet() const;

private:
	static std::chrono::steady_clock::time_point startTime;
	const Pipeline* const pipeline;
	VkBuffer uniformBuffer;
	VkDeviceMemory uniformBufferMemory;
	void* uniformBufferMapped;
	VkDescriptorSet descriptorSet;

};