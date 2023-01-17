#include "Queue.h"

Queue::Queue(VkInstance* vkInstance) :
	vkInstance(vkInstance)
{
	pickPhysicalDevice();
}

void Queue::pickPhysicalDevice() {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(*vkInstance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(*vkInstance, &deviceCount, devices.data());
	physicalDevice = devices[0];
	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
	std::cout << deviceProperties.deviceName;
}