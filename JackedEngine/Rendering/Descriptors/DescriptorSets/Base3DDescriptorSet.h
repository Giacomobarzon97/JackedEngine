#pragma once
#include "Rendering/Descriptors/DescriptorSets/BaseDescriptorSet.h"
#include "Rendering/Descriptors/DescriptorPools/Base3DDescriptorPool.h"
#include "Rendering/Buffers/UniformBuffer.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

class Base3DDescriptorSet : public BaseDescriptorSet{
public:
	Base3DDescriptorSet(const Device& device, const Base3DDescriptorPool& descriptorPool);
	Base3DDescriptorSet(Base3DDescriptorSet&) = delete;
	virtual ~Base3DDescriptorSet() override;

	Base3DDescriptorSet &operator=(Base3DDescriptorSet &) = delete;

	virtual void UpdateDescriptorSet() const override;

private:
	static std::chrono::steady_clock::time_point startTime;
	struct UniformBufferObject {
		glm::mat4 mvp;
	};
	const UniformBuffer mvpUniform;

};