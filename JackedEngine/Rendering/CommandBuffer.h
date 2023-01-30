#pragma once

#include "Rendering/Device.h"
#include "Rendering/SwapChain.h"
#include "Rendering/Pipeline.h"

class CommandBuffer {
public:
	CommandBuffer(Device* device, SwapChain* swapChain, int maxFramesInFlight);
	CommandBuffer(CommandBuffer&) = delete;
	~CommandBuffer();

	CommandBuffer &operator=(CommandBuffer &) = delete;

	void PresentCommand(Pipeline* pipeline);

	static void FramebufferResizeCallback(void * buffer);

private:
	Device* device;
	SwapChain* swapChain;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	bool framebufferResized = false;
	uint32_t currentFrame = 0;
	int maxFramesInFlight;
};