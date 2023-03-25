#include "GraphicalCommandBuffer.h"

GraphicalCommandBuffer::GraphicalCommandBuffer(Device& device, const Object3DPipeline& object3DPipeline) :
	BaseCommandBuffer(device),
	device(device),
	object3DPipeline(object3DPipeline)
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

void GraphicalCommandBuffer::Draw(const GPUModel& model, const FrameDescriptorSet& frameDescriptorSet, const ObjectDescriptorSet& objectDescriptorSet) const {
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, object3DPipeline.GetGraphicsPipeline());

	VkBuffer vertexBuffers[] = { 
		model.GetPositionsBufferAllocation().GetBuffer(),
		model.GetTextureBufferAllocation().GetBuffer()
	};
	VkDeviceSize offsets[] = { 0 , 0};
	vkCmdBindVertexBuffers(commandBuffer, 0, 2, vertexBuffers, offsets);
	vkCmdBindIndexBuffer(commandBuffer, model.GetIndexBufferAllocation().GetBuffer(), 0, CPUModel::GetIndexType());


	VkViewport viewport;
	VkRect2D scissor;

	object3DPipeline.GetScreenData(viewport, scissor);

	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	std::array<VkDescriptorSet, 2> descriptorSets{};
	descriptorSets[0] = frameDescriptorSet.GetDescriptorSet();
	descriptorSets[1] = objectDescriptorSet.GetDescriptorSet();

	vkCmdBindDescriptorSets(
		commandBuffer, 
		VK_PIPELINE_BIND_POINT_GRAPHICS, 
		object3DPipeline.GetPipelineLayout(),
		0, 
		static_cast<uint32_t>(descriptorSets.size()),
		descriptorSets.data(), 
		0, 
		nullptr
	);

	vkCmdDrawIndexed(commandBuffer, model.GetNumberOfIndices(), 1, 0, 0, 0);
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
	return vkQueuePresentKHR(device.GetPresentQueue(), &presentInfo);
}

