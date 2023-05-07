#include "Renderer.h"

Renderer::Renderer(BaseBackend& backend) :
	backend(backend)
{
	frameUniform = backend.CreateUniform("FrameData", sizeof(FrameData));
	modelUniform = backend.CreateUniform("ModelData", sizeof(ModelData));
}

const ModelReference Renderer::CreateModel(CPUBaseModel& model) {
	return backend.CreateModel(model);
}

const ImageReference Renderer::CreateImage(CPUImage& image) {
	return backend.CreateImage(image);
}

void Renderer::BeginFrame() {
	backend.BeginFrame();
}

void Renderer::UpdateCamera(const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix) {
	FrameData frameData{};
	frameData.viewMatrix = viewMatrix;
	frameData.projectionMatrix = projectionMatrix;
	backend.UpdateUniform(frameUniform, &frameData);
}

void Renderer::Draw(const ModelReference modelReference, const ImageReference imageReference, const glm::mat4 modelMatrix, const ShaderType shaderType) {
	ModelData modelData{};
	modelData.modelMatrix = modelMatrix;
	backend.UpdateUniform(modelUniform, &modelData);

	backend.BindPipeline(shaderType);
	backend.BindModel(modelReference);
	backend.BindUniform(0, frameUniform);
	backend.BindUniform(1, modelUniform);
	backend.BindImage(2, imageReference);
	backend.Draw();
}

void Renderer::EndFrame() {
	backend.EndFrame();
}