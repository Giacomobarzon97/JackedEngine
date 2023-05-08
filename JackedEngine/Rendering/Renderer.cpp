#include "Renderer.h"

Renderer::Renderer(BaseBackend& backend) :
	backend(backend)
{
	frameUniform = backend.CreateUniform("FrameData", sizeof(FrameData));
	modelUniform = backend.CreateUniform("ModelData", sizeof(ModelData));

	PipelineCreateInfo pipelineCreateInfo{};

	pipelineCreateInfo.id = "GenericObject3D";
	pipelineCreateInfo.vertexShader = "Backends/Shaders/CompiledShaders/object.vert.spv";
	pipelineCreateInfo.fragmentShader = "Backends/Shaders/CompiledShaders/object.frag.spv";
	pipelineCreateInfo.attachments.resize(3);
	pipelineCreateInfo.attachments[0] = AttachmentType::UNIFORM;
	pipelineCreateInfo.attachments[1] = AttachmentType::UNIFORM;
	pipelineCreateInfo.attachments[2] = AttachmentType::IMAGE;
	pipelineCreateInfo.vertices.resize(2);
	pipelineCreateInfo.vertices[0].type = FLOAT_32;
	pipelineCreateInfo.vertices[0].size = 4;
	pipelineCreateInfo.vertices[1].type = FLOAT_32;
	pipelineCreateInfo.vertices[1].size = 2;

	pipelineMap[ShaderType::OBJECT3D] = backend.CreatePipeline(pipelineCreateInfo);

	pipelineCreateInfo.id = "Skybox";
	pipelineCreateInfo.vertexShader = "Backends/Shaders/CompiledShaders/skybox.vert.spv";
	pipelineCreateInfo.fragmentShader = "Backends/Shaders/CompiledShaders/skybox.frag.spv";
	pipelineCreateInfo.attachments.clear();
	pipelineCreateInfo.attachments.resize(3);
	pipelineCreateInfo.attachments[0] = AttachmentType::UNIFORM;
	pipelineCreateInfo.attachments[1] = AttachmentType::UNIFORM;
	pipelineCreateInfo.attachments[2] = AttachmentType::IMAGE;
	pipelineCreateInfo.vertices.clear();
	pipelineCreateInfo.vertices.resize(1);
	pipelineCreateInfo.vertices[0].type = FLOAT_32;
	pipelineCreateInfo.vertices[0].size = 4;

	pipelineMap[ShaderType::SKYBOX] = backend.CreatePipeline(pipelineCreateInfo);

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

	backend.BindPipeline(pipelineMap[shaderType]);
	backend.BindModel(modelReference);
	backend.BindUniform(0, frameUniform);
	backend.BindUniform(1, modelUniform);
	backend.BindImage(2, imageReference);
	backend.Draw();
}

void Renderer::EndFrame() {
	backend.EndFrame();
}