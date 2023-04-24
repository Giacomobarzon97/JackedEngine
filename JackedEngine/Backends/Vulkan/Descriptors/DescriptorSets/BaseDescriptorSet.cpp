#include "BaseDescriptorSet.h"

BaseDescriptorSet::BaseDescriptorSet(const Device& device) :
	device(device)
{}

BaseDescriptorSet::~BaseDescriptorSet() {}

const VkDescriptorSet& BaseDescriptorSet::GetDescriptorSet() const {
	return descriptorSet;
}