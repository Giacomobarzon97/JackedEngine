#include "Renderer.h"

Renderer::Renderer(BaseWindow* window, int maxFramesInFlight) {
	device = new Device(window);
	pipeline = new Pipeline(device);
	vertexBuffer = new VertexBuffer(device);
	commandBuffer = new CommandBuffer(device, maxFramesInFlight);
	window->SetBufferResizeCallback(commandBuffer, CommandBuffer::FramebufferResizeCallback);
}

Renderer::~Renderer() {
	delete commandBuffer;
	delete pipeline;
	delete vertexBuffer;
	delete device;
}

void Renderer::DrawFrame() {
	commandBuffer->PresentCommand(pipeline,vertexBuffer);
}

void Renderer::Reset() {
	vkDeviceWaitIdle(*device->GetLogicalDevice());
}
