#include "Renderer.h"

Renderer::Renderer(BaseBackend& backend) :
	backend(backend)
{
	frameUniform = backend.CreateUniform("FrameData", sizeof(FrameData));
	lightsBuffer = backend.CreateStorageBuffer("PointLightsBuffer", sizeof(LightData), maxLights);

	PipelineCreateInfo pipelineCreateInfo{};

	pipelineCreateInfo.id = "GenericObject3D";
	pipelineCreateInfo.vertexShader = "Backends/Shaders/CompiledShaders/object.vert.spv";
	pipelineCreateInfo.fragmentShader = "Backends/Shaders/CompiledShaders/object.frag.spv";
	pipelineCreateInfo.attachments.resize(5);
	pipelineCreateInfo.attachments[0] = AttachmentType::UNIFORM;
	pipelineCreateInfo.attachments[1] = AttachmentType::UNIFORM;
	pipelineCreateInfo.attachments[2] = AttachmentType::IMAGE;
	pipelineCreateInfo.attachments[3] = AttachmentType::STORAGE_BUFFER;
	pipelineCreateInfo.attachments[4] = AttachmentType::UNIFORM;
	pipelineCreateInfo.vertices.resize(3);
	pipelineCreateInfo.vertices[0].type = CPUPositionVertex::GetVertexType();
	pipelineCreateInfo.vertices[0].size = CPUPositionVertex::GetNumberOfComponents();
	pipelineCreateInfo.vertices[1].type = CPUTextureVertex::GetVertexType();
	pipelineCreateInfo.vertices[1].size = CPUTextureVertex::GetNumberOfComponents();
	pipelineCreateInfo.vertices[2].type = CPUNormalVertex::GetVertexType();
	pipelineCreateInfo.vertices[2].size = CPUNormalVertex::GetNumberOfComponents();

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
	pipelineCreateInfo.vertices[0].type = CPUPositionVertex::GetVertexType();
	pipelineCreateInfo.vertices[0].size = CPUPositionVertex::GetNumberOfComponents();

	skyboxPipeline = backend.CreatePipeline(pipelineCreateInfo);

	lights.resize(maxLights);
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

const RendererMaterialUniformReference Renderer::CreateMaterialUniformReference(std::string name) {
	int asd = sizeof(MaterialUniformData);
	return RendererMaterialUniformReference(*this, backend.CreateUniform("MaterialUniform_" + name, sizeof(MaterialUniformData)));
}

const RendererLightReference Renderer::CreateLight() {
	if (currentLightsNumber >= maxLights) {
		throw std::runtime_error("Max point lights number exceeded");
	}
	RendererLightReference reference(*this, lights[currentLightsNumber]);
	currentLightsNumber++;
	return reference;
}

void Renderer::BeginFrame() {
	backend.BeginFrame();
	frameData.nLights = currentLightsNumber;
	backend.UpdateUniform(frameUniform, &frameData);
}

void Renderer::UpdateViewMatrix(glm::mat4 view) {
	frameData.viewMatrix = view;
}

void Renderer::UpdateProjectionMatrix(glm::mat4 proj) {
	frameData.projectionMatrix = proj;
}

void Renderer::DrawTextured3DMesh(const RendererModelReference modelReference, const RendererImage2DReference imageReference, const RendererMeshUniformReference uniformReference, const RendererMaterialUniformReference materialReference) {
	backend.UpdateUniform(materialReference.uniformReference, &materialReference.materialData);
	backend.UpdateStorageBuffer(lightsBuffer, lights.data(), currentLightsNumber);
	backend.BindPipeline(meshPipeline);
	backend.BindModel(modelReference.modelReference);
	backend.BindUniform(0, frameUniform);
	backend.BindUniform(1, uniformReference.uniformReference);
	backend.BindImage2D(2, imageReference.imageReference);
	backend.BindStorageBuffer(3, lightsBuffer);
	backend.BindUniform(4, materialReference.uniformReference);
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

RendererMaterialUniformReference::RendererMaterialUniformReference() {}
RendererMaterialUniformReference::RendererMaterialUniformReference(Renderer& renderer, BackendUniformReference uniformReference) :
	renderer(&renderer),
	uniformReference(uniformReference)
{}
void RendererMaterialUniformReference::SetAmbientCoefficients(glm::vec3 coefficients) {
	materialData.kAmbient = { coefficients, 1 };
}
void RendererMaterialUniformReference::SetDiffuseCoefficients(glm::vec3 coefficients) {
	materialData.kDiffuse = { coefficients, 1 };
}
void RendererMaterialUniformReference::SetSpecularCoefficients(glm::vec3 coefficients) {
	materialData.kSpecular = { coefficients, 1 };
}
void RendererMaterialUniformReference::SetShininess(uint32_t shininess) {
	materialData.shininess = shininess;
}

RendererLightReference::RendererLightReference(){}
RendererLightReference::RendererLightReference(Renderer& renderer, Renderer::LightData& pointLightData) :
	renderer(&renderer),
	lightData(&pointLightData)
{}
void RendererLightReference::SetPosition(glm::vec4 position){
	lightData->position = position;
}
void RendererLightReference::SetLightColor(glm::vec3 color) {
	lightData->lightColor = { color, 1 };
}