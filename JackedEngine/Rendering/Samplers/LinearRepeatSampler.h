#pragma once
#include "Rendering/Samplers/BaseSampler.h"

class LinearRepeatSampler : public BaseSampler{
public:
	LinearRepeatSampler(const Device& device);
	LinearRepeatSampler(LinearRepeatSampler&) = delete;
	~LinearRepeatSampler();
	LinearRepeatSampler& operator=(LinearRepeatSampler&) = delete;
};