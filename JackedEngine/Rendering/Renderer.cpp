#include "Renderer.h"

Renderer::Renderer(BaseBackend& backend) :
	backend(backend)
{
	frameUniform = backend.CreateUniform("FrameData", sizeof(FrameData));

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

const BackendModelReference Renderer::CreateModel(CPUBaseModel& model) {
	return backend.CreateModel(model);
}

const BackendImageReference Renderer::CreateImage(CPUImage& image) {
	return backend.CreateImage(image);
}

const BackendUniformReference Renderer::CreateMeshUniform(std::string name) {
	return backend.CreateUniform(name, sizeof(MeshUniformData));
}

void Renderer::BeginFrame() {
	backend.BeginFrame();
}

void Renderer::UpdateFrameData(const FrameData& frameData) {
	backend.UpdateUniform(frameUniform, &frameData);
}

void Renderer::UpdateMeshUniformData(const BackendUniformReference uniformReference, const MeshUniformData& meshUniformData) {
	backend.UpdateUniform(uniformReference, &meshUniformData);
}

void Renderer::Draw(const BackendModelReference modelReference, const BackendImageReference imageReference, const BackendUniformReference uniformReference, const ShaderType shaderType) {
	backend.BindPipeline(pipelineMap[shaderType]);
	backend.BindModel(modelReference);
	backend.BindUniform(0, frameUniform);
	backend.BindUniform(1, uniformReference);
	backend.BindImage(2, imageReference);
	backend.Draw();
}

void Renderer::EndFrame() {
	backend.EndFrame();
}