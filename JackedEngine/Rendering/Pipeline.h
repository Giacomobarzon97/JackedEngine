#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "Utils/FileIOr.h"
#include "Rendering/Device.h"

class Pipeline {
public:
	Pipeline(Device* device, std::string vertShaderPath, std::string fragShaderPath);

private:
	Device * device;

	VkShaderModule createShaderModule(const std::vector<char>& code);
};