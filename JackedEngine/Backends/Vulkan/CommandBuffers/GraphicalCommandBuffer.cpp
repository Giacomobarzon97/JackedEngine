#include "GraphicalCommandBuffer.h"

GraphicalCommandBuffer::GraphicalCommandBuffer(Device& device) :
	BaseCommandBuffer(device),
	device(device)
{
	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	if (vkCreateSemaphore(device.GetLogicalDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
		vkCreateSemaphore(device.GetLogicalDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
		vkCreateFence(device.GetLogicalDevice(), &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {

		throw std::runtime_error("failed to create synchronization objects for a frame!");
	}

}

GraphicalCommandBuffer::~GraphicalCommandBuffer() {
	vkDestroySemaphore(device.GetLogicalDevice(), renderFinishedSemaphore, nullptr);
	vkDestroySemaphore(device.GetLogicalDevice(), imageAvailableSemaphore, nullptr);
	vkDestroyFence(device.GetLogicalDevice(), inFlightFence, nullptr);
}

void GraphicalCommandBuffer::BeginRenderPass() {
	if (currentState == CommandBufferState::Recording) {
		throw std::runtime_error("another renderpass is currently running");
	}
	currentState = CommandBufferState::Recording;

	vkWaitForFences(device.GetLogicalDevice(), 1, &inFlightFence, VK_TRUE, UINT64_MAX);

	VkResult result = vkAcquireNextImageKHR(device.GetLogicalDevice(), device.GetSwapChain(), UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		device.RecreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}

	vkResetFences(device.GetLogicalDevice(), 1, &inFlightFence);
	vkResetCommandBuffer(commandBuffer, 0);

	VkExtent2D swapChainExtent = device.GetSwapChainExtent();

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0; // Optional
	beginInfo.pInheritanceInfo = nullptr; // Optional
	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = device.GetRenderPass();
	renderPassInfo.framebuffer = device.GetSwapChainFramebuffer(imageIndex);
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapChainExtent;
	std::vector<VkClearValue> clearValues = device.GetClearValues();
	renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	renderPassInfo.pClearValues = clearValues.data();
	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void GraphicalCommandBuffer::BindPipeline(const BasePipeline& pipeline) {
	if (currentState == CommandBufferState::Idle) {
		throw std::runtime_error("Can't bind pipeline while in idle state");
	}
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.GetGraphicsPipeline());
	bindedPipeline = &pipeline;
}

void GraphicalCommandBuffer::BindModel(const GPUModel& model) {
	if (currentState == CommandBufferState::Idle) {
		throw std::runtime_error("Can't bind model while in idle state");
	}
	if (!bindedPipeline.has_value()) {
		throw std::runtime_error("No pipeline has been bound");
	}
	std::vector<VkBuffer> vertexBuffers = model.GetBuffers();
	std::vector<VkDeviceSize> vertexOffsets;
	vertexOffsets.resize(vertexBuffers.size());
	for (uint8_t i = 0; i < vertexBuffers.size(); i++) {
		vertexOffsets[i] = 0;
	}

	vkCmdBindVertexBuffers(commandBuffer, 0, static_cast<uint32_t>(vertexBuffers.size()), vertexBuffers.data(), vertexOffsets.data());
	vkCmdBindIndexBuffer(commandBuffer, model.GetIndexBufferAllocation().GetBuffer(), 0, GPUModel::GetIndexType());
	bindedModel = &model;
}

void GraphicalCommandBuffer::BindDescriptorSet(const BaseDescriptorSet& descriptorSet, const uint32_t location) {
	if (currentState == CommandBufferState::Idle) {
		throw std::runtime_error("Can't bind descriptor while in idle state");
	}
	if (!bindedPipeline.has_value()) {
		throw std::runtime_error("No pipeline has been bound");
	}

	vkCmdBindDescriptorSets(
		commandBuffer,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		bindedPipeline.value()->GetPipelineLayout(),
		location,
		1,
		&descriptorSet.GetDescriptorSet(),
		0,
		nullptr
	);
}

void GraphicalCommandBuffer::Draw() const {
	if (currentState == CommandBufferState::Idle) {
		throw std::runtime_error("Can't execute draw command while in idle state");
	}
	if (!bindedPipeline.has_value()) {
		throw std::runtime_error("No pipeline has been bound");
	}
	if (!bindedModel.has_value()) {
		throw std::runtime_error("No model has been bound");
	}

	VkViewport viewport;
	VkRect2D scissor;

	bindedPipeline.value()->GetScreenData(viewport, scissor);

	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	vkCmdDrawIndexed(commandBuffer, bindedModel.value()->GetNumberOfIndices(), 1, 0, 0, 0);
}

const VkResult GraphicalCommandBuffer::EndRenderPass() {
	if (currentState == CommandBufferState::Idle) {
		throw std::runtime_error("no renderpass has been started");
	}
	currentState = CommandBufferState::Idle;

	vkCmdEndRenderPass(commandBuffer);

	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphore };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;
	VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;
	if (vkQueueSubmit(device.GetGraphicsQueue(), 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}
	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	VkSwapchainKHR swapChains[] = { device.GetSwapChain() };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional

	bindedModel.reset();
	bindedPipeline.reset();

	return vkQueuePresentKHR(device.GetPresentQueue(), &presentInfo);
}

