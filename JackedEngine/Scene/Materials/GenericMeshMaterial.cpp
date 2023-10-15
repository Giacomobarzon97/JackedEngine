#include "GenericMeshMaterial.h"

GenericMeshMaterial::GenericMeshMaterial(const std::string diffuseTexturePath) {
	CPUImage2D texture(diffuseTexturePath);
	diffuseTextureRef = JackedEngine::GetRenderer().CreateImage2D(texture);
}

const RendererImage2DReference GenericMeshMaterial::GetDiffuseTexture() const {
	return diffuseTextureRef;
}