#pragma once

#include "Rendering/Device.h"
#include "Rendering/SwapChain.h"
#include "Rendering/Pipeline.h"

class CommandBuffer {
public:
	CommandBuffer(Device* device, SwapChain* swapChain, Pipeline* pipeline);
	CommandBuffer(CommandBuffer&) = delete;
	~CommandBuffer();

	CommandBuffer &operator=(CommandBuffer &) = delete;

	void PresentCommand();
	void Reset();

private:
	Device* device;
	SwapChain* swapChain;
	Pipeline* pipeline;
	VkCommandPool commandPool;
	VkCommandBuffer commandBuffer;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
};