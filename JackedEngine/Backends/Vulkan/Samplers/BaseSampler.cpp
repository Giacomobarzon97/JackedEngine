#include "BaseSampler.h"

BaseSampler::BaseSampler(const Device& device) :
	device(device)
{}

BaseSampler::~BaseSampler() {
	vkDestroySampler(device.GetLogicalDevice(), sampler, nullptr);
}

const VkSampler& BaseSampler::GetSampler() const {
	return sampler;
}