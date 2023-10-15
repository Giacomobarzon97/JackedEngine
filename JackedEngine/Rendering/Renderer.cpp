#include "Renderer.h"

Renderer::Renderer(BaseBackend& backend) :
	backend(backend)
{
	frameUniform = backend.CreateUniform("FrameData", sizeof(FrameData));
	pointLightsBuffer = backend.CreateStorageBuffer("PointLightsBuffer", sizeof(PointLightData), maxPointLights);

	PipelineCreateInfo pipelineCreateInfo{};

	pipelineCreateInfo.id = "GenericObject3D";
	pipelineCreateInfo.vertexShader = "Backends/Shaders/CompiledShaders/object.vert.spv";
	pipelineCreateInfo.fragmentShader = "Backends/Shaders/CompiledShaders/object.frag.spv";
	pipelineCreateInfo.attachments.resize(4);
	pipelineCreateInfo.attachments[0] = AttachmentType::UNIFORM;
	pipelineCreateInfo.attachments[1] = AttachmentType::UNIFORM;
	pipelineCreateInfo.attachments[2] = AttachmentType::IMAGE;
	pipelineCreateInfo.attachments[3] = AttachmentType::STORAGE_BUFFER;
	pipelineCreateInfo.vertices.resize(2);
	pipelineCreateInfo.vertices[0].type = FLOAT_32;
	pipelineCreateInfo.vertices[0].size = 4;
	pipelineCreateInfo.vertices[1].type = FLOAT_32;
	pipelineCreateInfo.vertices[1].size = 2;

	meshPipeline = backend.CreatePipeline(pipelineCreateInfo);

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

	skyboxPipeline = backend.CreatePipeline(pipelineCreateInfo);

}

const RendererModelReference Renderer::CreateModel(CPUBaseModel& model) {
	return RendererModelReference(*this, backend.CreateModel(model));
}

const RendererImage2DReference Renderer::CreateImage2D(CPUImage2D & image) {
	return RendererImage2DReference(*this, backend.CreateImage2D(image));
}

const RendererCubemapReference Renderer::CreateCubemap(CPUCubemap& image) {
	return RendererCubemapReference(*this, backend.CreateCubemap(image));
}

const RendererMeshUniformReference Renderer::CreateMeshUniform(std::string name) {
	return RendererMeshUniformReference(*this, backend.CreateUniform("MeshUniform_" + name, sizeof(MeshUniformData)));
}

void Renderer::BeginFrame() {
	backend.BeginFrame();
	backend.UpdateUniform(frameUniform, &frameData);
}

void Renderer::UpdateViewMatrix(glm::mat4 view) {
	frameData.viewMatrix = view;
}

void Renderer::UpdateProjectionMatrix(glm::mat4 proj) {
	frameData.projectionMatrix = proj;
}

void Renderer::DrawTextured3DMesh(const RendererModelReference modelReference, const RendererImage2DReference imageReference, const RendererMeshUniformReference uniformReference) {
	backend.BindPipeline(meshPipeline);
	backend.BindModel(modelReference.modelReference);
	backend.BindUniform(0, frameUniform);
	backend.BindUniform(1, uniformReference.uniformReference);
	backend.BindImage2D(2, imageReference.imageReference);
	backend.BindStorageBuffer(3, pointLightsBuffer);
	backend.Draw();
}

void Renderer::DrawSkybox(const RendererModelReference modelReference, const RendererCubemapReference imageReference, const RendererMeshUniformReference uniformReference) {
	backend.BindPipeline(skyboxPipeline);
	backend.BindModel(modelReference.modelReference);
	backend.BindUniform(0, frameUniform);
	backend.BindUniform(1, uniformReference.uniformReference);
	backend.BindCubemap(2, imageReference.cubemapReference);
	backend.Draw();
}

void Renderer::EndFrame() {
	backend.EndFrame();
}

RendererModelReference::RendererModelReference(){}
RendererModelReference::RendererModelReference(Renderer& renderer, BackendModelReference modelReference) :
	renderer(&renderer),
	modelReference(modelReference)
{}

RendererImage2DReference::RendererImage2DReference() {}
RendererImage2DReference::RendererImage2DReference(Renderer& renderer, BackendImage2DReference imageReference) :
	renderer(&renderer),
	imageReference(imageReference)
{}

RendererCubemapReference::RendererCubemapReference() {}
RendererCubemapReference::RendererCubemapReference(Renderer& renderer, BackendCubemapReference cubemapReference) :
	renderer(&renderer),
	cubemapReference(cubemapReference)
{}

RendererMeshUniformReference::RendererMeshUniformReference() {}
RendererMeshUniformReference::RendererMeshUniformReference(Renderer& renderer, BackendUniformReference uniformReference) :
	renderer(&renderer),
	uniformReference(uniformReference)
{}
void RendererMeshUniformReference::SetModelMatrix(glm::mat4 model) {
	meshData.modelMatrix = model;
}
void RendererMeshUniformReference::Update() const {
	renderer->backend.UpdateUniform(uniformReference, &meshData);
}