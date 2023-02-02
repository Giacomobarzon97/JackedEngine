#include "Renderer.h"

Renderer::Renderer(BaseWindow* window, int maxFramesInFlight) {
	uint32_t windowExtensionCount = 0;
	const char** windowExtensions = window->GetRequiredExtensions(&windowExtensionCount);
	std::vector<const char*> extensions(windowExtensions, windowExtensions + windowExtensionCount);

	instance = new Instance(window->GetWindowName(), extensions);
	window->InitiWindowSurface(instance->GetVkInstance(), instance->GetVkSurface());
	device = new Device(instance);
	swapChain = new SwapChain(instance, device, window);
	pipeline = new Pipeline(device, swapChain);

	QueueFamilyIndices queueFamilyIndices = device->GetQueueFamilyIndices();
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
	if (vkCreateCommandPool(*device->GetLogicalDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}

	vertexBuffer = new VertexBuffer(device, &commandPool);
	commandBuffer = new CommandBuffer(device, swapChain, maxFramesInFlight);
	window->SetBufferResizeCallback(commandBuffer, CommandBuffer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	delete commandBuffer;
	delete pipeline;
	delete swapChain;
	delete vertexBuffer;
	vkDestroyCommandPool(*device->GetLogicalDevice(), commandPool, nullptr);
	delete device;
	delete instance;
}

void Renderer::DrawFrame() {
	commandBuffer->PresentCommand(pipeline,vertexBuffer);
}

void Renderer::Reset() {
	vkDeviceWaitIdle(*device->GetLogicalDevice());
}
