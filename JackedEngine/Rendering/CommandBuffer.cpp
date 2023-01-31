#include "CommandBuffer.h"

CommandBuffer::CommandBuffer(Device* device, SwapChain* swapChain, int maxFramesInFlight) :
	device(device),
	swapChain(swapChain),
	maxFramesInFlight(maxFramesInFlight)
{
	commandBuffers.resize(maxFramesInFlight);
	QueueFamilyIndices queueFamilyIndices = device->GetQueueFamilyIndices();
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
	if (vkCreateCommandPool(*device->GetLogicalDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();
	if (vkAllocateCommandBuffers(*device->GetLogicalDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}


	imageAvailableSemaphores.resize(maxFramesInFlight);
	renderFinishedSemaphores.resize(maxFramesInFlight);
	inFlightFences.resize(maxFramesInFlight);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < maxFramesInFlight; i++) {
		if (vkCreateSemaphore(*device->GetLogicalDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(*device->GetLogicalDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(*device->GetLogicalDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {

			throw std::runtime_error("failed to create synchronization objects for a frame!");
		}
	}

}

CommandBuffer::~CommandBuffer() {
	for (size_t i = 0; i < maxFramesInFlight; i++) {
		vkDestroySemaphore(*device->GetLogicalDevice(), renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(*device->GetLogicalDevice(), imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(*device->GetLogicalDevice(), inFlightFences[i], nullptr);
	}
	vkDestroyCommandPool(*device->GetLogicalDevice(), commandPool, nullptr);
}

void CommandBuffer::PresentCommand(Pipeline* pipeline, VertexBuffer* vertexBuffer) {
	vkWaitForFences(*device->GetLogicalDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

	uint32_t imageIndex;
	if (!swapChain->GetNextImageIndex(imageIndex, &imageAvailableSemaphores[currentFrame])) {
		return;
	}

	vkResetFences(*device->GetLogicalDevice(), 1, &inFlightFences[currentFrame]);
	vkResetCommandBuffer(commandBuffers[currentFrame], 0);

	VkExtent2D swapChainExtent = swapChain->GetSwapChainExtent();

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0; // Optional
	beginInfo.pInheritanceInfo = nullptr; // Optional
	if (vkBeginCommandBuffer(commandBuffers[currentFrame], &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = *swapChain->GetRenderPass();
	renderPassInfo.framebuffer = *swapChain->GetSwapChainFramebuffer(imageIndex);
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapChainExtent;
	VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;
	vkCmdBeginRenderPass(commandBuffers[currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(commandBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, *pipeline->GetGraphicsPipeline());

	VkBuffer vertexBuffers[] = { *vertexBuffer->GetVertexBuffer() };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(commandBuffers[currentFrame], 0, 1, vertexBuffers, offsets);

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapChainExtent.width);
	viewport.height = static_cast<float>(swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffers[currentFrame], 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;
	vkCmdSetScissor(commandBuffers[currentFrame], 0, 1, &scissor);

	vkCmdDraw(commandBuffers[currentFrame], 3, 1, 0, 0);
	vkCmdEndRenderPass(commandBuffers[currentFrame]);

	if (vkEndCommandBuffer(commandBuffers[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[currentFrame];
	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;
	if (vkQueueSubmit(*device->GetGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}
	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	VkSwapchainKHR swapChains[] = { *swapChain->GetSwapChain() };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional
	VkResult result = vkQueuePresentKHR(*device->GetPresentQueue(), &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		framebufferResized = false;
		swapChain->Recreate();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	currentFrame = (currentFrame + 1) % maxFramesInFlight;
}

void CommandBuffer::FramebufferResizeCallback(void * buffer) {
	CommandBuffer* cb = reinterpret_cast<CommandBuffer*>(buffer);
	cb->framebufferResized = true;
}
