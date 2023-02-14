#include "BaseDescriptorSet.h"

BaseDescriptorSet::BaseDescriptorSet(const Device* const device) :
	device(device)
{}

BaseDescriptorSet::~BaseDescriptorSet() {}

const VkDescriptorSet* const BaseDescriptorSet::GetDescriptorSet() const {
	return &descriptorSet;
}