#pragma once

#include "Rendering/Device.h"
#include "Rendering/SwapChain.h"
#include "Rendering/Pipeline.h"

class CommandBuffer {
public:
	CommandBuffer(Device* device, SwapChain* swapChain, Pipeline* pipeline, int maxFramesInFlight);
	CommandBuffer(CommandBuffer&) = delete;
	~CommandBuffer();

	CommandBuffer &operator=(CommandBuffer &) = delete;

	void PresentCommand();

private:
	Device* device;
	SwapChain* swapChain;
	Pipeline* pipeline;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	uint32_t currentFrame = 0;
	int maxFramesInFlight;
};