#include "GenericMeshMaterial.h"

GenericMeshMaterial::GenericMeshMaterial(const std::string name, const std::string diffuseTexturePath) : 
	BaseMaterial(name)
{
	CPUImage2D texture(diffuseTexturePath);
	diffuseTextureRef = JackedEngine::GetRenderer().CreateImage2D(texture);
}

const RendererImage2DReference GenericMeshMaterial::GetDiffuseTexture() const {
	return diffuseTextureRef;
}